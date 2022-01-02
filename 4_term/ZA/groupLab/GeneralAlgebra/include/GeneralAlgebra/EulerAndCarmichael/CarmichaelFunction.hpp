#pragma once

#include "GeneralAlgebra/PolynomialFactoring.hpp"
#include "GeneralAlgebra/LongArithmetic.hpp"
#include "GeneralAlgebra/LongNumber.hpp"

namespace GeneralAlgebra {
    template<int CellLength>
    LongNumber<CellLength> LCM(const std::vector<LongNumber<CellLength>>& Numbers) {
        LongNumber<CellLength> result = Numbers[0];
        for (long long i = 1; i < Numbers.size(); i++){
            result = (((Numbers[i] * result)) / (LongArithmetic::Gcd(Numbers[i], result)));
        }
        return result;
    }

    template<int CellLength>
    LongNumber<CellLength> CarmichaelFunction(const LongNumber<CellLength>& number) {
        std::vector<LongNumber<CellLength>> miniCarmichael;
        auto factors = naiveFactoringWithPowers(number);
        LongNumber<CellLength> to_add;
        LongNumber<CellLength> temp;
        LongNumber<CellLength> one(1);
        LongNumber<CellLength> two(2);
        LongNumber<CellLength> four(4);
        for (const auto& factor : factors) {
            to_add = LongArithmetic::FastPow(factor.first, (factor.second - one)) * (factor.first - one);
            temp = LongArithmetic::FastPow(factor.first, factor.second);
            auto powTwoChecker = LongArithmetic::DecompositionPowerTwo(temp);
            if ((temp > four) && (powTwoChecker.second == one)) {
                miniCarmichael.push_back(to_add / two);
            } else {
                miniCarmichael.push_back(to_add);
            }
        }
        return LCM(miniCarmichael);
    }
}