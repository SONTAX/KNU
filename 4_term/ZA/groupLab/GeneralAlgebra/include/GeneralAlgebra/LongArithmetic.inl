#include "IntegralInfo.hpp"

namespace GeneralAlgebra {

    template <LongNumberConcept T>
    T LongArithmetic::Add(const T& lhs, const T& rhs) {
        if (lhs.m_Sign == rhs.m_Sign)
            return ModAdd(lhs, rhs, lhs.m_Sign);

        if (lhs.m_Sign == Sign::Plus)
            return lhs.m_Length > rhs.m_Length ? ModSub(lhs, rhs, Sign::Plus) : ModSub(rhs, lhs, Sign::Minus);

        return lhs.m_Length > rhs.m_Length ? ModSub(lhs, rhs, Sign::Minus) : ModSub(rhs, lhs, Sign::Plus);
    }

    template <LongNumberConcept T>
    T LongArithmetic::Sub(const T& lhs, const T& rhs) {
        if (lhs.m_Sign == rhs.m_Sign) {
            if (lhs.m_Sign == Sign::Plus)
                return lhs >= rhs ? ModSub(lhs, rhs, Sign::Plus) : ModSub(rhs, lhs, Sign::Minus);

            return lhs >= rhs ? ModSub(rhs, lhs, Sign::Plus) : ModSub(lhs, rhs, Sign::Minus);
        }

        return LongArithmetic::ModAdd(lhs, rhs, lhs.m_Sign);
    }

    template <LongNumberConcept T>
    T LongArithmetic::HalfMul(const T& lhs, int rhs) {
        auto cellLimit  = lhs.GetCellLimit();
        auto maxSize    = std::max(lhs.GetMaxSize(), IntegralInfo::GetSize<T::GetCellLength()>(rhs));
        auto resultSize = lhs.GetActualSize() + IntegralInfo::GetSize<T::GetCellLength()>(rhs);

        T result;

        result.Resize(maxSize > resultSize ? maxSize : resultSize);
        result.m_Sign = lhs.m_Sign == IntegralInfo::GetSign(rhs) ? Sign::Plus : Sign::Minus;

        for (int i = 0, carry = 0; i < result.GetMaxSize(); ++i) {
            carry             = (i < lhs.GetActualSize() ? lhs.m_Data[i] : 0) * rhs + carry;
            result.m_Data[i]  = carry % cellLimit;
            carry            /= cellLimit;
        }

        result.Update();

        return result;
    }

    template <LongNumberConcept T>
    T LongArithmetic::NaiveMul(const T& lhs, const T& rhs) {
        auto cellLimit  = lhs.GetCellLimit();
        auto maxSize    = std::max(lhs.GetMaxSize(), rhs.GetMaxSize());
        auto resultSize = lhs.GetActualSize() + rhs.GetActualSize();
        auto carry      = 0;

        T result;

        result.Resize(maxSize > resultSize ? maxSize : resultSize);
        result.m_Sign = lhs.m_Sign == rhs.m_Sign ? Sign::Plus : Sign::Minus;

        for (int i = 0; i < rhs.GetActualSize(); ++i) {
            carry = 0;

            for (int j = 0; j < lhs.GetActualSize(); ++j) {
                auto& resultCell = result.m_Data[i + j];

                resultCell += rhs.m_Data[i] * lhs.m_Data[j] + carry;
                carry       = resultCell / cellLimit;
                resultCell %= cellLimit;
            }

            result.m_Data[i + lhs.GetActualSize()] = carry;
        }

        result.Update();

        return result;
    }

    template <LongNumberConcept T>
    T LongArithmetic::KaratsubaMul(const T& lhs, const T& rhs, int limit) {
        if (lhs.GetActualSize() <= limit || rhs.GetActualSize() <= limit)
            return NaiveMul(lhs, rhs);

        auto m = std::max(lhs.GetActualSize(), rhs.GetActualSize());
        auto m2 = m / 2 + m % 2;

        auto low1End  = m2 >= lhs.GetMaxSize() ? lhs.m_Data.end() : lhs.m_Data.begin() + m2;
        auto high1End = m >=  lhs.GetMaxSize() ? lhs.m_Data.end() : lhs.m_Data.begin() + m;

        auto low2End  = m2 >= rhs.GetMaxSize() ? rhs.m_Data.end() : rhs.m_Data.begin() + m2;
        auto high2End = m >=  rhs.GetMaxSize() ? rhs.m_Data.end() : rhs.m_Data.begin() + m;

        T low1(lhs.m_Data.begin(), low1End);
        T high1(low1End, high1End);

        T low2(rhs.m_Data.begin(), low2End);
        T high2(low2End, high2End);

        auto z0 = KaratsubaMul(low1, low2, limit);
        auto z1 = KaratsubaMul(low1 + high1, low2 + high2, limit);
        auto z2 = KaratsubaMul(high1, high2, limit);

        auto res = z2.ShiftLeft(m2 * 2 * T::GetCellLength()) + (z1 - z2 - z0).ShiftLeft(m2 * T::GetCellLength()) + z0;

        if (res.GetActualSize() < std::max(lhs.GetMaxSize(), rhs.GetMaxSize()))
            res.Resize(std::max(lhs.GetMaxSize(), rhs.GetMaxSize()));

        return res;
    }

    template <LongNumberConcept T>
    T LongArithmetic::HalfDiv(const T& lhs, int rhs) {
        return HalfDivImpl(lhs, rhs);
    }

    template <LongNumberConcept T>
    T LongArithmetic::NaiveDiv(const T& lhs, const T& rhs) {
        return NaiveDivImpl(lhs, rhs);
    }

    template <LongNumberConcept T>
    T LongArithmetic::LogDiv(const T& lhs, const T& rhs) {
        return LogDivImpl(lhs, rhs);
    }

    template <LongNumberConcept T>
    T LongArithmetic::HalfRem(const T& lhs, int rhs) {
        return HalfDivImpl(lhs, rhs, true);
    }

    template <LongNumberConcept T>
    T LongArithmetic::NaiveRem(const T& lhs, const T& rhs) {
        return NaiveDivImpl(lhs, rhs, true);
    }

    template <LongNumberConcept T>
    T LongArithmetic::LogRem(const T& lhs, const T& rhs) {
        return LogDivImpl(lhs, rhs, true);
    }

    template <LongNumberConcept T>
    T LongArithmetic::FastSquare(const T& number) {
        auto cellLimit  = number.GetCellLimit();
        auto maxSize    = number.GetMaxSize();
        auto actualSize = number.GetActualSize();
        auto resultSize = actualSize * 2;
        auto carry      = 0;

        T result;

        result.Resize(std::max(resultSize, maxSize));

        for (int i = 0; i < actualSize; ++i) {
            carry = 0;

            for (int j = i; j < actualSize; ++j) {
                auto& resultCell = result.m_Data[i + j];

                if (i == j)
                    resultCell += std::pow(number.m_Data[i], 2);
                else
                    resultCell += 2 * number.m_Data[i] * number.m_Data[j];

                resultCell += carry;
                carry       = resultCell / cellLimit;
                resultCell %= cellLimit;
            }

            result.m_Data[i + actualSize] += carry;
        }

        result.Update();

        return result;
    }

    template <LongNumberConcept T>
    T LongArithmetic::NaiveSquare(const T& number) {
        return NaiveMul(number, number);
    }

    template <LongNumberConcept T>
    T LongArithmetic::FastPow(const T& number, T pow) {
        std::vector<int>       binaryPowerRepresentation;
        T two(2);
        T one(1);

        if (pow.IsNegative())
            return T(0);

        while (pow) {
            T currentBit = pow % two;

            binaryPowerRepresentation.push_back(currentBit.ToInt32());
            pow /= two;
        }

        T result(1);

        for (size_t i = binaryPowerRepresentation.size() - 1; i >= 0 && i < binaryPowerRepresentation.size(); --i) {
            result = FastSquare(result);

            if (binaryPowerRepresentation[i] == 1)
                result *= number;
        }

        result.Update();

        return result;
    }

    template <LongNumberConcept T>
    std::pair<int, T> LongArithmetic::DecompositionPowerTwo(T number) {
        // Converts the number to the form: number = 2^s * t,
        // where t is odd.
        // Returns pair, where:
        // pair.first = s (int),
        // pair.second = t (LongNumber).
        T base(2);
        T remainder = number % base;

        int count = 0;
        while(!remainder && number){
            number /= base;
            remainder = number % base;
            count++;
        }

        return std::pair<int, T>(count, number);
    }

    template <LongNumberConcept T>
    short LongArithmetic::Jacobi(const T& number, const T& base) {
        // Returns Jacobi Symbol (number/base)
        // Can be improved when 'Factoring a number' will be ready

        short result;

        if(!number) return 0;
        if(number == T::One) return 1;

        std::pair<int, T> dec_number = DecompositionPowerTwo(number);

        T base_remainder_8  = base % T(8);

        if(dec_number.first % 2 == 0){
            result = 1;
        }
        else{
            if(base_remainder_8.ToInt() == 1 || base_remainder_8.ToInt() == 7)
                result = 1;
            if(base_remainder_8.ToInt() == 3 || base_remainder_8.ToInt() == 5)
                result = -1;
        }

        T base_remainder_4     = base % T(4);
        T remainder_a1         = dec_number.second % T(4);

        if(base_remainder_4.ToInt() == 3 && remainder_a1.ToInt() == 3)
            result *= -1;

        T additional_base = base % dec_number.second;

        return dec_number.second == T::One ? result : result * Jacobi(additional_base, dec_number.second);
    }

    template <LongNumberConcept T>
    std::string LongArithmetic::BinaryConversion(T number) {
        // Returns binary conversion of number

        std::string buffer;

        do
        {
            T b = number % T(2);
            std::string temp = b.ToString();
            buffer += temp[0];
            number = number / T(2);
        } while (number > T::Null);

        return std::string(buffer.crbegin(), buffer.crend());
    }

    template <LongNumberConcept T>
    T LongArithmetic::Gcd(const T& a,const T& b) {
        // Returns greatest common divisor of a and b

        // Everything divides 0
        if (!a)
            return b;

        if (!b)
            return a;

        // base case
        if (a == b)
            return a;

        return a > b ? Gcd(a - b, b) : Gcd(a, b - a);
    }

    template <LongNumberConcept T>
    T LongArithmetic::GetMaxByBinaryLength(int bits_count) {
        // May be improved(?)
        // Returns maximum that fit in number with binary lengths equals to bits_count

        T a(2);
        T result(1);
        for(int i = 0; i < bits_count; ++i)
            result *= a;
        return result;
    }

    template <LongNumberConcept T>
    T LongArithmetic::ModAdd(const T& lhs, const T& rhs, Sign sign) {
        auto cellLimit  = lhs.GetCellLimit();
        auto maxSize    = std::max(lhs.GetMaxSize(),    rhs.GetMaxSize()   );
        auto actualSize = std::max(lhs.GetActualSize(), rhs.GetActualSize());

        T result;

        result.Resize(maxSize + (maxSize == actualSize ? 1 : 0));
        result.m_Sign = sign;

        for (int i = 0, carry = 0; i < result.GetMaxSize(); ++i) {
            auto& resultCell = result.m_Data[i];

            resultCell  = (i < lhs.GetMaxSize() ? lhs.m_Data[i] : 0) + (i < rhs.GetMaxSize() ? rhs.m_Data[i] : 0) + carry;
            carry       = result.m_Data[i] / cellLimit;
            resultCell %= cellLimit;
        }

        result.Update();

        return result;
    }

    template <LongNumberConcept T>
    T LongArithmetic::ModSub(const T& lhs, const T& rhs, Sign sign) {
        auto cellLimit = lhs.GetCellLimit();
        T    result;

        result.Resize(std::max(lhs.GetMaxSize(), rhs.GetMaxSize()));
        result.m_Sign = sign;

        for (int i = 0, carry = 0; i < result.GetMaxSize(); ++i) {
            auto& resultCell = result.m_Data[i];

            resultCell  = (i < lhs.GetMaxSize() ? lhs.m_Data[i] : 0) - carry - (i < rhs.GetMaxSize() ? rhs.m_Data[i] : 0) + cellLimit;
            carry       = resultCell < cellLimit ? 1 : 0;
            resultCell %= cellLimit;
        }

        result.Update();

        return result;
    }

    template <LongNumberConcept T>
    T LongArithmetic::HalfDivImpl(const T& lhs, int rhs, bool returnRemainder) {
        T result;
        result.Resize(lhs.GetMaxSize());

        if (rhs == 0)
            throw std::invalid_argument("GeneralAlgebra::LongArithmetic::HalfDiv: Division by zero!");

        int second = std::abs(rhs);

        int remainder = 0;

        result.m_Sign = lhs.m_Sign == IntegralInfo::GetSign(rhs) ? Sign::Plus : Sign::Minus;

        for (int i = lhs.GetActualSize() - 1; i >= 0; --i) {
            remainder         = lhs.GetCellLimit() * remainder + lhs.m_Data[i];
            result.m_Data[i]  = remainder / second;
            remainder        %= second;
        }

        result.Update();

        return returnRemainder ? T(std::to_string(remainder), T::GetCellLength()) : result;
    }

    template <LongNumberConcept T>
    T LongArithmetic::NaiveDivImpl(const T& lhs, const T& rhs, bool returnRemainder) {
        if (!rhs)
            throw std::invalid_argument("GeneralAlgebra::LongArithmetic::NaiveDiv: Division by zero!");

        T result;
        T remainder;

        result.Resize(lhs.GetMaxSize());
        result.m_Sign = lhs.m_Sign == rhs.m_Sign ? Sign::Plus : Sign::Minus;

        remainder.Resize(rhs.GetMaxSize() + 1);

        LongNumber second = rhs;
        second.m_Sign = Sign::Plus;

        for (int i = lhs.GetActualSize() - 1; i >= 0; --i) {
            for (int j = remainder.GetActualSize(); j > 0; --j)
                remainder.m_Data[j] = remainder.m_Data[j - 1];

            remainder.m_Data[0] = lhs.m_Data[i];
            remainder.Update();

            int counter = 0;
            while (remainder >= second){
                counter++;
                remainder -= second;
            }

            result.m_Data[i] = counter;
        }

        result.Update();
        remainder.m_Sign = lhs.m_Sign;
        remainder.Update();

        return returnRemainder ? remainder : result;
    }

    template <LongNumberConcept T>
    T LongArithmetic::LogDivImpl(const T& lhs, const T& rhs, bool returnRemainder) {
        if (!rhs)
            throw std::invalid_argument("GeneralAlgebra::LongArithmetic::LogDiv: Division by zero!");

        T result;
        T remainder;
        T logCellSize(static_cast<int>(std::log(lhs.GetCellLimit())));

        result.Resize(lhs.GetMaxSize());
        result.m_Sign = lhs.m_Sign == rhs.m_Sign ? Sign::Plus : Sign::Minus;

        remainder.Resize(rhs.GetMaxSize() + 1);

        LongNumber second = rhs;
        second.m_Sign = Sign::Plus;

        for (int i = lhs.GetActualSize() - 1; i >= 0; --i) {
            for (int j = remainder.GetActualSize(); j > 0; --j)
                remainder.m_Data[j] = remainder.m_Data[j - 1];

            remainder.m_Data[0] = lhs.m_Data[i];
            remainder.Update();

            int left = 1;
            int right = lhs.GetCellLimit();
            int counter = 0;

            if (remainder >= second) {

                if (remainder - second * logCellSize > T()) {
                    while (right != left) {
                        int mid = (left + right) / 2;

                        T middle(mid, T::GetCellLength());

                        if (middle * second > remainder)
                            right = mid;
                        else
                            left = mid + 1;
                    }
                    T divider(left - 1, T::GetCellLength());

                    auto res = remainder - second * divider;
                    remainder = res;

                    result.m_Data[i] = left - 1;

                } else {

                    while (remainder >= second){
                        counter++;
                        remainder -= second;
                    }

                    result.m_Data[i] = counter;
                }
            }

        }

        result.Update();
        remainder.m_Sign = lhs.m_Sign;
        remainder.Update();

        return returnRemainder ? remainder : result;
    }

} // namespace GeneralAlgebra