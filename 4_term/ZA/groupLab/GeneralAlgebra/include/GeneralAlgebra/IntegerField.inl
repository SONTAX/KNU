#include <Random/Random.hpp>

namespace GeneralAlgebra {

    namespace Internal {

        template <IntegerFieldNumberConcept T>
        T ExtendedEuclid(const T& r1, const T& r2, const T& x1, const T& x2, const T& y1, const T& y2) {
            T r3 = r1 - r2 * (r1 / r2);
            T x3 = x1 - x2 * (r1 / r2);
            T y3 = y1 - y2 * (r1 / r2);

            return r3 ? ExtendedEuclid(r2, r3, x2, x3, y2, y3) : y2;
        }

    } // Internal

    template <IntegerFieldNumberConcept T>
    IntegerField<T>::IntegerField(const T& primeNumber)
        : m_PrimeNumber(primeNumber) {

        // TODO: check number for it's prime
    }

    template <IntegerFieldNumberConcept T>
    IntegerField<T>::IntegerField(T&& primeNumber)
        : m_PrimeNumber(primeNumber) {

        // TODO: check number for it's prime
    }

    template <IntegerFieldNumberConcept T>
    bool IntegerField<T>::SetPrimeNumber(const T& primeNumber) {
        // TODO: check number for it's prime

        m_PrimeNumber = primeNumber;

        return true;
    }
    
    template <IntegerFieldNumberConcept T>
    bool IntegerField<T>::SetPrimeNumber(T&& primeNumber) {
        // TODO: check number for it's prime

        m_PrimeNumber = primeNumber;

        return true;
    }
    
    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::GetInverse(const T& number) const {
        auto result = Internal::ExtendedEuclid(m_PrimeNumber, number, T(1), T(0), T(0), T(1));
        return result < T() ? result + m_PrimeNumber : result;
    }

    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::Add(const T& lhs, const T& rhs) const {
        return (lhs % m_PrimeNumber + rhs % m_PrimeNumber) % m_PrimeNumber;
    }

    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::Sub(const T& lhs, const T& rhs) const {
        auto result = (lhs % m_PrimeNumber - rhs % m_PrimeNumber);
        return result < T() ? result + m_PrimeNumber : result;
    }

    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::Mul(const T& lhs, const T& rhs) const {
        return (lhs % m_PrimeNumber * rhs % m_PrimeNumber) % m_PrimeNumber;
    }

    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::Div(const T& lhs, const T& rhs) const {
        return Mul(lhs, GetInverse(rhs));
    }

    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::Pow(T num, T pow) const {
        if(pow.IsNegative()) {
            num = GetInverse(num);
            pow = T() - pow;
        }

        num %= m_PrimeNumber;

        return num.Pow(pow) % m_PrimeNumber;
    }

    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::MontgomeryMul(const T& a, const T& b) const {
        // TODO: Need to be improved
        
        constexpr auto CellLength = T::GetCellLength();
        std::string n_bits = LongArithmetic::BinaryConversion(m_PrimeNumber);
        int reducerBits = (n_bits.length() / 8 + 1) * 8;
        T r = LongArithmetic::GetMaxByBinaryLength<CellLength>(reducerBits);

         assert(r > m_PrimeNumber && LongArithmetic::Gcd(r, m_PrimeNumber) == LongNumber<CellLength>::One);

        T _r = GetInverse(r);
        T k = (r * _r - LongNumber<CellLength>::One) / m_PrimeNumber;
        T _a = Mul(a,r);
        T _b = Mul(b,r);

        IntegerField add_field(r);
        T x = _a * _b;
        T s = add_field.Mul(x, k);
        T t = x + s * m_PrimeNumber;
        T u = Mul(t, _r);
        T _c;
        if (u < m_PrimeNumber)
            _c = u;
        else _c = u - m_PrimeNumber;
        LongNumber c = Mul(_c, _r);
        return c;
    }

    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::MontgomeryPow(const T& number, const T& pow) const {
        constexpr auto CellLength = T::GetCellLength();
        if(!pow) return LongNumber<CellLength>::One;

        T b(1);
        T temp = number;
        std::string binary_k = LongArithmetic::BinaryConversion(pow);
        binary_k = std::string(binary_k.crbegin(), binary_k.crend());

        if(binary_k[0] == '1') b = number;
        for(int i = 1; i <= binary_k.length(); ++i){
            temp = Mul(temp, temp);
            if(binary_k[i] == '1') b = Mul(temp, b);
        }
        return b;
    }

    template <IntegerFieldNumberConcept T>
    std::pair<T, T> IntegerField<T>::Sqrt(const T& number) const {
        std::pair<T, T> result(0,0);
        if(LongArithmetic::Jacobi(number, m_PrimeNumber) == -1)
            return result;

        T unit(1);
        T negative_unit(-1);
        T b(1);

        while (LongArithmetic::Jacobi(b, m_PrimeNumber) != -1){
            int size = Ng::Random::Get(1, m_PrimeNumber.GetLength());

            T random_ln(Ng::Random::GetString(size, 48, 57));
            b = random_ln % m_PrimeNumber;
        }

        std::pair<int, T> q = LongArithmetic::DecompositionPowerTwo(m_PrimeNumber + negative_unit);
        T inverse_number    = GetInverse(number);
        T c                 = MontgomeryPow(b, q.second);
        T power             = (q.second + unit) / T(2);
        T r                 = MontgomeryPow(number, power);

        for(int i = 1; i < q.first; ++i){
            int bits_count = q.first - i - 1;
            T pow = LongArithmetic::GetMaxByBinaryLength<T>(bits_count);
            T add = Mul(r*r, inverse_number);
            T d = MontgomeryPow(add, pow);

            if( d == negative_unit || d == m_PrimeNumber - unit) r = Mul(r, c);
            c = Pow(c, T(2));
        }

        result.first = r;
        result.second = r * negative_unit;

        return result;
    }

    template <IntegerFieldNumberConcept T>
    T IntegerField<T>::NaiveMul(const T& lhs, const T& rhs) const {
        return (lhs % m_PrimeNumber * rhs % m_PrimeNumber) % m_PrimeNumber;
    }

} // namespace GeneralAlgebra