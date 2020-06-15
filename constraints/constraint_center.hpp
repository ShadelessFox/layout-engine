#pragma once

#include "constraint.hpp"

namespace GUI {
namespace Constraint {

    template <typename T>
    class CenterConstraint : public Constraint<T> {
    public:
        double calculate(const Component::Component* parent, const Component::Component& current) const noexcept override;
    };

    template <>
    class CenterConstraint<OffsXConstraint> : public Constraint<OffsXConstraint> {
    public:
        double calculate(const Component::Component* parent, const Component::Component& current) const noexcept override
        {
            return Constraint::calculate(parent, current) + (parent->compute<SizeXConstraint>() - current.compute<SizeXConstraint>()) / 2.0;
        }
    };

    template <>
    class CenterConstraint<OffsYConstraint> : public Constraint<OffsYConstraint> {
    public:
        double calculate(const Component::Component* parent, const Component::Component& current) const noexcept override
        {
            return Constraint::calculate(parent, current) + (parent->compute<SizeYConstraint>() - current.compute<SizeYConstraint>()) / 2.0;
        }
    };

    using HorizontalCenterConstraint = CenterConstraint<OffsXConstraint>;
    using VerticalCenterConstraint = CenterConstraint<OffsYConstraint>;

}
}