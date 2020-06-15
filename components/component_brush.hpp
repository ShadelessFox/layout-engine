#pragma once

#include "component.hpp"

namespace GUI {
namespace Component {

    class BrushComponent : public Component {
    public:
        BrushComponent(SDL_Color color);

        void render(SDL_Renderer* ctx) override;

    private:
        SDL_Color _color;
    };

}
}