#include "component_brush.hpp"
#include "../constraints/constraint.hpp"

GUI::Component::BrushComponent::BrushComponent(SDL_Color color)
    : _color(color)
{
}

void GUI::Component::BrushComponent::render(SDL_Renderer* ctx)
{
    const SDL_Rect rect {
        static_cast<int>(_constraints.x().offset()->calculate(_parent, *this)),
        static_cast<int>(_constraints.y().offset()->calculate(_parent, *this)),
        static_cast<int>(_constraints.x().size()->calculate(_parent, *this)),
        static_cast<int>(_constraints.y().size()->calculate(_parent, *this)),
    };

    SDL_SetRenderDrawColor(ctx, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(ctx, &rect);
}