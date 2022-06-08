#pragma once

#include "LongNumber.hpp"
#include "LongArithmetic.hpp"
#include "PolynomialFactoring.hpp"

namespace GeneralAlgebra {
    template<typename T>
    template<int CellLength>
    LongNumber<CellLength> LCM(std::vector<T> Numbers) {
        LongNumber<CellLength> result = Numbers[0];
        for (T i = T(1); i < Numbers.size(); i++){
            result = (((Numbers[i] * result)) / (Gcd(Numbers[i], result)));
        }
        return result;
    }

    template<typename T>
    template<int CellLength>
    LongNumber<CellLength> CarmichaelFunction(T n){
        using LN = LongNumber<CellLength>;
        std::map<T, T> Factoring = naiveFactoringWithPowers(n);
        std::vector<T> elements;
        LongNumber<CellLength> temp;
        for (const auto& elem : PrimeNumbers) {
            //if
            temp = FastPow(elem.first, elem.second - LN(1));
            elements.push_back(temp);
        }
        return LCM<T>(elements);
    }
}