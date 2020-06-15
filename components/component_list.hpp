#pragma once

#include "component.hpp"

#include <memory>
#include <vector>

namespace GUI {
namespace Component {

    class ListComponent : public Component {
    public:
        void add(std::unique_ptr<Component>&& child) noexcept;

    protected:
        std::vector<std::unique_ptr<Component>> _children;
    };

    class HorizontalListComponent : public ListComponent {
    public:
        void render(SDL_Renderer* ctx) override;
    };

    class VerticalListComponent : public ListComponent {
    public:
        void render(SDL_Renderer* ctx) override;
    };

}
}