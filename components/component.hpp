#pragma once

#include <SDL2/SDL.h>

#include "../constraints/constraints.hpp"

namespace GUI {
namespace Component {

    class Component {
    public:
        virtual void render(SDL_Renderer* ctx) = 0;

        template <typename T>
        double compute() const noexcept;

        inline void adopt(Component* parent) noexcept
        {
            _parent = parent;
        }

        inline const Constraint::Constraints& constraints() const noexcept
        {
            return _constraints;
        }

        inline Constraint::Constraints& constraints() noexcept
        {
            return _constraints;
        }

    protected:
        Constraint::Constraints _constraints;
        Component* _parent { nullptr };
    };

}
}