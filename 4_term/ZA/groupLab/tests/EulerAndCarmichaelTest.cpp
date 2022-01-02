#include <doctest/doctest.h>

#include "GeneralAlgebra/EulerAndCarmichael/EulerFunction.hpp"
#include "GeneralAlgebra/EulerAndCarmichael/CarmichaelFunction.hpp"

using namespace GeneralAlgebra;

constexpr auto CellLength = 5;

using LN = LongNumber<CellLength>;

TEST_CASE("Testing the Euler`s function") {
    CHECK(EulerFunction(LN(16)) == LN(8));
    CHECK(EulerFunction(LN(53481)) == LN(35652));
    CHECK(EulerFunction(LN(176051)) == LN(176050));
    CHECK(EulerFunction(LN(35184372088832)) == LN(17592186044416));
    CHECK(EulerFunction(LN(1513526425474621918)) == LN(725138041162106880));
}

TEST_CASE("Testing the Carmichael`s function") {
    CHECK(CarmichaelFunction(LN(16)) == LN(4));
    CHECK(CarmichaelFunction(LN(53481)) == LN(17826));
    CHECK(CarmichaelFunction(LN(176051)) == LN(176050));
    CHECK(CarmichaelFunction(LN(35184372088832)) == LN(8796093022208));
    CHECK(CarmichaelFunction(LN(1513526425474621918)) == LN(839280140233920));
}
