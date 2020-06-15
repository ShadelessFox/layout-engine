#include "component_frame.hpp"
#include "../constraints/constraint_pixel.hpp"

GUI::Component::FrameComponent::FrameComponent(std::unique_ptr<Component>&& child, unsigned int width, unsigned int height)
    : _child(std::move(child))
    , _width(width)
    , _height(height)
{
    _child->adopt(this);
    _constraints.x() = Constraint::PixelConstraint<Constraint::OffsXConstraint>(0);
    _constraints.y() = Constraint::PixelConstraint<Constraint::OffsYConstraint>(0);
    _constraints.x() += Constraint::PixelConstraint<Constraint::SizeXConstraint>(width);
    _constraints.y() += Constraint::PixelConstraint<Constraint::SizeYConstraint>(height);
}

void GUI::Component::FrameComponent::resize(unsigned int width, unsigned int height) noexcept
{
    _width = width;
    _height = height;
    _constraints.x() += Constraint::PixelConstraint<Constraint::SizeXConstraint>(width);
    _constraints.y() += Constraint::PixelConstraint<Constraint::SizeYConstraint>(height);
}

void GUI::Component::FrameComponent::render(SDL_Renderer* ctx)
{
    _child->render(ctx);
}