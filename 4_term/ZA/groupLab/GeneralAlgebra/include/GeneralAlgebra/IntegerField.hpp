#pragma once

#include "LongNumber.hpp"

namespace GeneralAlgebra {

    template <typename T>
    concept IntegerFieldNumberConcept = IntegralConcept<T> || LongNumberConcept<T>;

    template <IntegerFieldNumberConcept T>
    class IntegerField {
    public:
        IntegerField() = default;
        explicit IntegerField(const T& primeNumber);
        explicit IntegerField(T&& primeNumber);
        ~IntegerField() noexcept = default;

    public:
        [[nodiscard]] const T& GetPrimeNumber() const { return m_PrimeNumber; }

        bool SetPrimeNumber(const T& primeNumber);
        bool SetPrimeNumber(T&& primeNumber);

        T GetInverse(const T& number) const;

        T Add(const T& lhs, const T& rhs) const;
        T Sub(const T& lhs, const T& rhs) const;
        T Mul(const T& lhs, const T& rhs) const;
        T Div(const T& lhs, const T& rhs) const;

        T Pow(T num, T pow) const;

        T MontgomeryMul(const T& a,const T& b) const;
        T MontgomeryPow(const T& number, const T& pow) const;

        std::pair<T, T> Sqrt(const T& number) const;

    private:
        T NaiveMul(const T& lhs, const T& rhs) const;

    private:
        T m_PrimeNumber;

    }; // class IntegerField

} // namespace GeneralAlgebra

#include "IntegerField.inl"