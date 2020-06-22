#include <SDL2/SDL.h>

#include "components/component_brush.hpp"
#include "components/component_frame.hpp"
#include "components/component_list.hpp"
#include "constraints/constraint_center.hpp"
#include "constraints/constraint_relative.hpp"
#include "constraints/constraint_pixel.hpp"

class Counter {
public:
    Counter(double updateRate)
        : _updateRate(updateRate)
    {
    }

    void tick()
    {
        _totalFrames++;

        _lastFrameTime = SDL_GetTicks();
        _delta = (_lastFrameTime - _prevFrameTime) / 1000.0;
        _updateDelta += _delta;
        _prevFrameTime = _lastFrameTime;

        if (_updateDelta > _updateRate) {
            _fps = _totalFrames / _updateDelta;
            _totalFrames = 0;
            _updateDelta -= _updateRate;
        }
    }

    double value() const
    {
        return _fps;
    }

    double delta() const
    {
        return _delta;
    }

private:
    double _updateRate;
    double _delta { 0.0 };
    double _updateDelta { 0.0 };
    double _fps { 0.0 };
    unsigned int _prevFrameTime { 0 };
    unsigned int _lastFrameTime { 0 };
    unsigned int _totalFrames { 0 };
};

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window* window = SDL_CreateWindow("Application", 100, 100, 800, 800, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    using namespace GUI::Constraint;
    using namespace GUI::Component;

    HorizontalListComponent list0;
    list0.constraints().x() = HorizontalCenterConstraint();
    list0.constraints().y() = VerticalCenterConstraint();
    list0.constraints().x() += WidthRelativeConstraint(1.0);
    list0.constraints().y() += HeightRelativeConstraint(1.0);

    BrushComponent brush0 { SDL_Color { 120, 40, 150, SDL_ALPHA_OPAQUE } };
    brush0.constraints().x() = HorizontalCenterConstraint();
    brush0.constraints().y() = VerticalCenterConstraint();
    brush0.constraints().x() += WidthRelativeConstraint(0.9);
    brush0.constraints().y() += HeightRelativeConstraint(0.9);

    BrushComponent brush1 { SDL_Color { 120, 40, 150, SDL_ALPHA_OPAQUE } };
    brush1.constraints().x() = HorizontalCenterConstraint();
    brush1.constraints().y() = VerticalCenterConstraint();
    brush1.constraints().x() += WidthPixelConstraint(4.0);
    brush1.constraints().y() += HeightRelativeConstraint(1.0);

    BrushComponent brush2 { SDL_Color { 120, 40, 150, SDL_ALPHA_OPAQUE } };
    brush2.constraints().x() = HorizontalCenterConstraint();
    brush2.constraints().y() = VerticalCenterConstraint();
    brush2.constraints().x() += WidthRelativeConstraint(0.9);
    brush2.constraints().y() += HeightRelativeConstraint(0.9);

    list0.add(std::make_unique<BrushComponent>(std::move(brush0)));
    list0.add(std::make_unique<BrushComponent>(std::move(brush1)));
    list0.add(std::make_unique<BrushComponent>(std::move(brush2)));

    FrameComponent frame {
        std::make_unique<HorizontalListComponent>(std::move(list0)),
        800,
        800
    };

    Counter counter { 0.5 };

    for (bool running = true; running; counter.tick()) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    int width, height;
                    SDL_GetWindowSize(window, &width, &height);
                    frame.resize(width, height);
                }
                break;
            }
        }

        char buffer[100];
        sprintf(buffer, "Average fps: %.0f", counter.value());
        SDL_SetWindowTitle(window, buffer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        frame.render(renderer);
        SDL_RenderPresent(renderer);
    }

    return 0;
}
