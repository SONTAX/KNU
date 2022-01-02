#pragma once

#include "IntegerField.hpp"

namespace GeneralAlgebra {

    template <typename T>
    concept EllipticCurveNumberConcept = IntegralConcept<T> || LongNumberConcept<T>;

    template <EllipticCurveNumberConcept T>
    struct Point {
        T X = T();
        T Y = T();
    };

    template <EllipticCurveNumberConcept T>
    class EllipticCurve {
    public:
        using Point = Point<T>;

    public:
        EllipticCurve(const T& a, const T& b, const T& primeNumber);
        ~EllipticCurve() noexcept = default;

    public:
        [[nodiscard]] inline const T& GetPrimeNumber() const { return m_Field.GetPrimeNumber(); }
        [[nodiscard]] inline const T& GetA() const { return m_A; }
        [[nodiscard]] inline const T& GetB() const { return m_B; }

        void SetPrimeNumber(const T& primeNumber);
        void SetA(const T& a);
        void SetB(const T& b);

        Point GetInverse(const Point& point);
        Point Add(const Point& lhs, const Point& rhs);

    private:
        IntegerField<T> m_Field;
        T               m_A;
        T               m_B;

    }; // class EllipticCurve

} // namespace GeneralAlgebra

#include "EllipticCurve.inl"