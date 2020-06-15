#pragma once

#include "constraint.hpp"

namespace GUI {
namespace Constraint {

    template <typename T>
    class RelativeConstraint : public Constraint<T> {
    public:
        RelativeConstraint(double value)
            : _value(value)
        {
            SDL_assert(value >= 0.0 && value <= 1.0);
        }

        double calculate(const Component::Component* parent, const Component::Component& current) const noexcept override
        {
            return Constraint<T>::calculate(parent, current) + parent->compute<T>() * _value;
        }

    private:
        double _value;
    };

    using XRelativeConstraint = RelativeConstraint<OffsXConstraint>;
    using YRelativeConstraint = RelativeConstraint<OffsYConstraint>;
    using WidthRelativeConstraint = RelativeConstraint<SizeXConstraint>;
    using HeightRelativeConstraint = RelativeConstraint<SizeYConstraint>;
}
}