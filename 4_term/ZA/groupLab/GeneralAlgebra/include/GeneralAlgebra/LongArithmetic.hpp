#pragma once

namespace GeneralAlgebra {

    template <int CellLength>
    class LongNumber;

    enum class Sign;

    template <typename T>
    concept LongNumberConcept =
        std::is_same_v<T, LongNumber<1>> ||
        std::is_same_v<T, LongNumber<2>> ||
        std::is_same_v<T, LongNumber<3>> ||
        std::is_same_v<T, LongNumber<4>> ||
        std::is_same_v<T, LongNumber<5>> ||
        std::is_same_v<T, LongNumber<6>> ||
        std::is_same_v<T, LongNumber<7>> ||
        std::is_same_v<T, LongNumber<8>> ||
        std::is_same_v<T, LongNumber<9>>;

    enum class Operation : int { None = 0, Add, Sub, Mul, Div, Rem };

    class LongArithmetic {
    public:
        template <LongNumberConcept T>
        static T Add(const T& lhs, const T& rhs);

        template <LongNumberConcept T>
        static T Sub(const T& lhs, const T& rhs);

        template <LongNumberConcept T>
        static T HalfMul(const T& lhs, int rhs);

        template <LongNumberConcept T>
        static T NaiveMul(const T& lhs, const T& rhs);

        template <LongNumberConcept T>
        static T KaratsubaMul(const T& lhs, const T& rhs, int limit = 512);

        template <LongNumberConcept T>
        static T HalfDiv(const T& lhs, int rhs);

        template <LongNumberConcept T>
        static T NaiveDiv(const T& lhs, const T& rhs);

        template <LongNumberConcept T>
        static T LogDiv(const T& lhs, const T& rhs);

        template <LongNumberConcept T>
        static T HalfRem(const T& lhs, int rhs);

        template <LongNumberConcept T>
        static T NaiveRem(const T& lhs, const T& rhs);

        template <LongNumberConcept T>
        static T LogRem(const T& lhs, const T& rhs);

        template <LongNumberConcept T>
        static T FastSquare(const T& number);

        template <LongNumberConcept T>
        static T NaiveSquare(const T& number);

        template <LongNumberConcept T>
        static T FastPow(const T& num, T pow);

        template <LongNumberConcept T>
        static std::pair<int, T> DecompositionPowerTwo(T number);

        template <LongNumberConcept T>
        static short Jacobi(const T& number, const T& base);

        template <LongNumberConcept T>
        static std::string BinaryConversion(T number);

        template <LongNumberConcept T>
        static T Gcd(const T& a,const T& b);

        template <LongNumberConcept T>
        static T GetMaxByBinaryLength(int bits_count);

    private:
        template <LongNumberConcept T>
        static T ModAdd(const T& lhs, const T& rhs, Sign sign);

        template <LongNumberConcept T>
        static T ModSub(const T& lhs, const T& rhs, Sign sign);

        template <LongNumberConcept T>
        static T HalfDivImpl(const T& lhs, int rhs, bool returnRemainder = false);

        template <LongNumberConcept T>
        static T NaiveDivImpl(const T& lhs, const T& rhs, bool returnRemainder = false);

        template <LongNumberConcept T>
        static T LogDivImpl(const T& lhs, const T& rhs, bool returnRemainder = false);

    }; // class LongArithmetic

} // namespace GeneralAlgebra

#include "LongArithmetic.inl"