#pragma once

#include "constraint.hpp"

namespace GUI {
namespace Constraint {

    template <typename T>
    class PixelConstraint : public Constraint<T> {
    public:
        PixelConstraint(double value)
            : _value(value)
        {
        }

        double calculate(const Component::Component* parent, const Component::Component& current) const noexcept override
        {
            return Constraint<T>::calculate(parent, current) + static_cast<double>(_value);
        }

    private:
        double _value;
    };

    using XPixelConstraint = PixelConstraint<OffsXConstraint>;
    using YPixelConstraint = PixelConstraint<OffsYConstraint>;
    using WidthPixelConstraint = PixelConstraint<SizeXConstraint>;
    using HeightPixelConstraint = PixelConstraint<SizeYConstraint>;

}
}