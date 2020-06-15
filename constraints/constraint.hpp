#pragma once

#include "../components/component.hpp"
#include "constraints.hpp"

namespace GUI {
namespace Constraint {

    template <typename T>
    class Constraint {
    public:
        virtual double calculate(const Component::Component* parent, const Component::Component& current) const noexcept
        {
            if (parent == nullptr)
                return 0.0;

            if (std::is_same<OffsXConstraint, T>::value)
                return parent->compute<OffsXConstraint>();

            if (std::is_same<OffsYConstraint, T>::value)
                return parent->compute<OffsYConstraint>();

            return 0.0;
        }
    };

}
}

template <>
inline double GUI::Component::Component::compute<GUI::Constraint::OffsXConstraint>() const noexcept { return _constraints.x().offset()->calculate(_parent, *this); }

template <>
inline double GUI::Component::Component::compute<GUI::Constraint::OffsYConstraint>() const noexcept { return _constraints.y().offset()->calculate(_parent, *this); }

template <>
inline double GUI::Component::Component::compute<GUI::Constraint::SizeXConstraint>() const noexcept { return _constraints.x().size()->calculate(_parent, *this); }

template <>
inline double GUI::Component::Component::compute<GUI::Constraint::SizeYConstraint>() const noexcept { return _constraints.y().size()->calculate(_parent, *this); }