#include "component_list.hpp"
#include "../constraints/constraint_pixel.hpp"
#include "../constraints/constraint_relative.hpp"

class DummyFrameComponent : public GUI::Component::Component {
public:
    void render(SDL_Renderer* ctx) override
    {
    }
};

void GUI::Component::ListComponent::add(std::unique_ptr<Component>&& child) noexcept
{
    _children.push_back(std::move(child));
}

void GUI::Component::HorizontalListComponent::render(SDL_Renderer* ctx)
{
    const double width = _parent->compute<Constraint::SizeXConstraint>() / _children.size();
    double offset = 0;

    DummyFrameComponent frame;
    frame.adopt(this);
    frame.constraints().y() = Constraint::PixelConstraint<Constraint::OffsYConstraint>(0);
    frame.constraints().x() += Constraint::PixelConstraint<Constraint::SizeXConstraint>(width);
    frame.constraints().y() += Constraint::RelativeConstraint<Constraint::SizeYConstraint>(1.0);

    auto id = 0;
    for (auto& child : _children) {
        child->adopt(this);
        frame.constraints().x() = Constraint::PixelConstraint<Constraint::OffsXConstraint>(offset);
        child->adopt(&frame);
        child->render(ctx);

        offset += width;
    }
}

void GUI::Component::VerticalListComponent::render(SDL_Renderer* ctx)
{
    const double height = _parent->compute<Constraint::SizeYConstraint>() / _children.size();
    double offset = 0;

    DummyFrameComponent frame;
    frame.adopt(this);
    frame.constraints().x() = Constraint::PixelConstraint<Constraint::OffsXConstraint>(0);
    frame.constraints().x() += Constraint::RelativeConstraint<Constraint::SizeXConstraint>(1.0);
    frame.constraints().y() += Constraint::PixelConstraint<Constraint::SizeYConstraint>(height);

    for (auto& child : _children) {
        frame.constraints().y() = Constraint::PixelConstraint<Constraint::OffsYConstraint>(offset);
        child->adopt(&frame);
        child->render(ctx);
        offset += height;
    }
}