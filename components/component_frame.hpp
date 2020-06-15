#pragma once

#include "component.hpp"

namespace GUI {
namespace Component {

    class FrameComponent : public Component {
    public:
        FrameComponent(std::unique_ptr<Component>&& child, unsigned int width, unsigned int height);

        void render(SDL_Renderer* ctx) override;

        void resize(unsigned int width, unsigned int height) noexcept;

        inline const Component* child() const noexcept { return _child.get(); }

        inline unsigned int width() const noexcept { return _width; }

        inline unsigned int height() const noexcept { return _height; }

    private:
        friend class Component;

        std::unique_ptr<Component> _child;
        unsigned int _width;
        unsigned int _height;
    };

}
}