#pragma once

#include "LongNumber.hpp"
#include "PolynomialFactoring.hpp"

namespace GeneralAlgebra {
    template<typename T>
    template<int CellLength>
    LongNumber<CellLength> EulerFunction(T n) {
        using LN = LongNumber<CellLength>;
        LongNumber<CellLength> result = n;
        LongNumber<CellLength> temp;
        std::map<T, T> PrimeNumbers = naiveFactoringWithPowers(n);
        for (const auto& elem : PrimeNumbers) {
            temp = LongNumber.One / elem.first;
            result *= (LongNumber.One - temp);
        }
        return result;
    }
}