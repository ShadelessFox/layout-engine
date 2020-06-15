#pragma once

#include <memory>

namespace GUI {
namespace Constraint {
    template <typename T>
    class Constraint;

    struct OffsXConstraint;
    struct OffsYConstraint;
    struct SizeXConstraint;
    struct SizeYConstraint;

    class Constraints {
    public:
        template <typename T, typename U>
        class Proxy {
        public:
            template <typename Ts>
            inline Proxy& operator=(Ts&& value) noexcept
            {
                _offs = std::make_shared<Ts>(std::move(value));
                return *this;
            }

            template <typename Us>
            inline Proxy& operator+=(Us&& value) noexcept
            {
                _size = std::make_shared<Us>(std::move(value));
                return *this;
            };

            inline const Constraint<T>* offset() const noexcept
            {
                return _offs.get();
            }

            inline const Constraint<U>* size() const noexcept
            {
                return _size.get();
            }

        private:
            std::shared_ptr<Constraint<T>> _offs;
            std::shared_ptr<Constraint<U>> _size;
        };

        inline const Proxy<OffsXConstraint, SizeXConstraint>& x() const noexcept { return _x; }
        inline Proxy<OffsXConstraint, SizeXConstraint>& x() noexcept { return _x; }

        inline const Proxy<OffsYConstraint, SizeYConstraint>& y() const noexcept { return _y; }
        inline Proxy<OffsYConstraint, SizeYConstraint>& y() noexcept { return _y; }

    private:
        Proxy<OffsXConstraint, SizeXConstraint> _x;
        Proxy<OffsYConstraint, SizeYConstraint> _y;
    };
}
}