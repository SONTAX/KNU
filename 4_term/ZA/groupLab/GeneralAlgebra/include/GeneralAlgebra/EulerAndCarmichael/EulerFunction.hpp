#pragma once

#include "GeneralAlgebra/PolynomialFactoring.hpp"
#include "GeneralAlgebra/LongArithmetic.hpp"
#include "GeneralAlgebra/LongNumber.hpp"

namespace GeneralAlgebra {
    template<int CellLength>
    LongNumber<CellLength> EulerFunction(const LongNumber<CellLength>& number) {
        LongNumber<CellLength> result(1);
        LongNumber<CellLength> one(1);
        auto factors = naiveFactoringWithPowers(number);
        for (const auto& factor: factors) {
            result *= (LongArithmetic::FastPow(factor.first, factor.second - one) * (factor.first - one));
        }
        return result;
    }
}