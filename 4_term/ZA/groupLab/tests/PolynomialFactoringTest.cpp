#include <doctest/doctest.h>

#include "GeneralAlgebra/PolynomialFactoring.hpp"
#include "GeneralAlgebra/LongNumber.hpp"

using namespace GeneralAlgebra;

constexpr auto CellLength = 5;

TEST_CASE("Testing the pollardFactoring") {
  CHECK(!(455459 % pollardFactoring(455459)));
  CHECK(!(35 % pollardFactoring(35)));
  CHECK(!(72 % pollardFactoring(72)));
  CHECK(!(455 % pollardFactoring(455)));
}

TEST_CASE("Testing the naiveFactoring") {
  CHECK(!(455459 % naiveFactoring(455459)[0]));
  CHECK(!(35 % naiveFactoring(35)[0]));
  CHECK(!(72 % naiveFactoring(72)[0]));
  CHECK(!(455 % naiveFactoring(455)[0]));
}

TEST_CASE("Testing the naiveFactoringWithPowers") {
  CHECK(!(455459 % naiveFactoringWithPowers(455459).begin()->first));
  CHECK(!(35 % naiveFactoringWithPowers(35).begin()->first));
  CHECK(!(72 % naiveFactoringWithPowers(72).begin()->first));
  CHECK(!(455 % naiveFactoringWithPowers(455).begin()->first));
}

using LN = LongNumber<CellLength>;

TEST_CASE("Testing the naiveFactoring with LongNumper") {
  CHECK(!(LN(455459) % naiveFactoring(LN(455459))[0]));
  CHECK(!(LN(35) % naiveFactoring(LN(35))[0]));
  CHECK(!(LN(72) % naiveFactoring(LN(72))[0]));
  CHECK(!(LN(455) % naiveFactoring(LN(455))[0]));
}

TEST_CASE("Testing the naiveFactoringWithPowers with LongNumper") {
  CHECK(!(LN(455459) % naiveFactoringWithPowers(LN(455459)).begin()->first));
  CHECK(!(LN(35) % naiveFactoringWithPowers(LN(35)).begin()->first));
  CHECK(!(LN(72) % naiveFactoringWithPowers(LN(72)).begin()->first));
  CHECK(!(LN(455) % naiveFactoringWithPowers(LN(455)).begin()->first));
}
