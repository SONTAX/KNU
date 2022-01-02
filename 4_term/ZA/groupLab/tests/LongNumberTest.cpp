#include <iostream>

#include <doctest/doctest.h>

#include <GeneralAlgebra/LongNumber.hpp>

template <int CellLength>
void Constructor() {
    using LongNumber = GeneralAlgebra::LongNumber<CellLength>;

    LongNumber a;
    LongNumber b("-123", 20);
    LongNumber c(-1);

    CHECK(a.ToString() == "0");
    CHECK(a.GetMaxSize() == 1);
    CHECK(a.GetActualSize() == 1);
    CHECK(a.GetLength() == 1);

    CHECK(b.ToString() == "-123");
    CHECK(b.GetActualSize() == (b.GetLength() / CellLength + (b.GetLength() % CellLength == 0 ? 0 : 1)));
    CHECK(b.GetLength() == 3);

    CHECK(c.ToString() == "-1");
    CHECK(c.GetLength() == 1);

    CHECK_THROWS_AS(b.SetString("-123o123"), const std::invalid_argument&);
    CHECK(b.ToString() == "-123");

    b.SetNumber(123123);
    CHECK(b.ToString() == "123123");
}

template <int CellLength>
void ComparisonOperators() {
    using LongNumber = GeneralAlgebra::LongNumber<CellLength>;

    LongNumber a("1123");
    LongNumber b("-2141");
    LongNumber c("1123", 50);

    SUBCASE("Operator <") {
        CHECK((a < b) == false);
        CHECK((a < c) == false);
        CHECK((b < a) == true);
        CHECK((b < c) == true);
        CHECK((c < a) == false);
        CHECK((c < b) == false);
    }

    SUBCASE("Operator <=") {
        CHECK((a <= b) == false);
        CHECK((a <= c) == true);
        CHECK((b <= a) == true);
        CHECK((b <= c) == true);
        CHECK((c <= a) == true);
        CHECK((c <= b) == false);
    }

    SUBCASE("Operator >") {
        CHECK((a > b) == true);
        CHECK((a > c) == false);
        CHECK((b > a) == false);
        CHECK((b > c) == false);
        CHECK((c > a) == false);
        CHECK((c > b) == true);
    }

    SUBCASE("Operator >=") {
        CHECK((a >= b) == true);
        CHECK((a >= c) == true);
        CHECK((b >= a) == false);
        CHECK((b >= c) == false);
        CHECK((c >= a) == true);
        CHECK((c >= b) == true);
    }

    SUBCASE("Operator !=") {
        CHECK((a != b) == true);
        CHECK((a != c) == false);
        CHECK((b != a) == true);
        CHECK((b != c) == true);
        CHECK((c != a) == false);
        CHECK((c != b) == true);
    }

    SUBCASE("Operator ==") {
        CHECK((a == b) == false);
        CHECK((a == c) == true);
        CHECK((b == a) == false);
        CHECK((b == c) == false);
        CHECK((c == a) == true);
        CHECK((c == b) == false);
    }
}

template <int CellLength>
void ArithmeticOperators() {
    using LongNumber = GeneralAlgebra::LongNumber<CellLength>;

    LongNumber a("15");
    LongNumber b("76", 20);

    SUBCASE("Add") {
        auto result = a + b;

        CHECK(result.ToString() == "91");
        CHECK(result.GetLength() == 2);
    }

    SUBCASE("Sub") {
        auto result = a - b;

        CHECK(result.ToString() == "-61");
        CHECK(result.GetLength() == 2);
    }

    SUBCASE("Mul") {
        auto result = a * b;

        CHECK(result.ToString() == "1140");
        CHECK(result.GetLength() == 4);
    }

    SUBCASE("Div") {
        CHECK((a / b).ToString() == "0");
    }

    SUBCASE("Remainder") {
        CHECK((a % b).ToString() == "15");
    }
}

template <int CellLength>
void LongArithmeticOperators(){
    using LongNumber = GeneralAlgebra::LongNumber<CellLength>;

    SUBCASE("First") {
        LongNumber a("1515352642547467987365");
        LongNumber b("76123642754112354255");
        CHECK((a + b).ToString() == "1591476285301580341620");
        CHECK((a - b).ToString() == "1439228999793355633110");
        CHECK((a * b).ToString() == "115354163207783569874640347871066743988075");
        CHECK((a / b).ToString() == "19");
        CHECK((a % b).ToString() == "69003430219333256520");
    }

    SUBCASE("Second") {
        LongNumber a("1000000000000000000000000000000000000000000000000000");
        LongNumber b("-1");
        CHECK((a + b).ToString() == "999999999999999999999999999999999999999999999999999");
        CHECK((a - b).ToString() == "1000000000000000000000000000000000000000000000000001");
        CHECK((a * b).ToString() == "-1000000000000000000000000000000000000000000000000000");
        CHECK((a / b).ToString() == "-1000000000000000000000000000000000000000000000000000");
        CHECK((a % b).ToString() == "0");
    }

    SUBCASE("Third") {
        LongNumber a("0");
        LongNumber b("1233653532654");
        CHECK((a + b).ToString() == "1233653532654");
        CHECK((a - b).ToString() == "-1233653532654");
        CHECK((a * b).ToString() == "0");
        CHECK((a / b).ToString() == "0");
        CHECK((a % b).ToString() == "0");
    }

    SUBCASE("Fourth") {
        LongNumber a("-999999999999999999999999999999999999999999999999999");
        LongNumber b("-132652521");
        CHECK((a + b).ToString() == "-1000000000000000000000000000000000000000000132652520");
        CHECK((a - b).ToString() == "-999999999999999999999999999999999999999999867347478");
        CHECK((a * b).ToString() == "132652520999999999999999999999999999999999999999999867347479");
        CHECK((a / b).ToString() == "7538492238681238481702130636476935104761408");
        CHECK((a % b).ToString() == "-125290431");
    }

    SUBCASE("Fifth") {
        LongNumber a("1");
        LongNumber b("0");
        CHECK((a + b).ToString() == "1");
        CHECK((a - b).ToString() == "1");
        CHECK((a * b).ToString() == "0");
        CHECK_THROWS_AS(a / b, const std::invalid_argument&);
        CHECK_THROWS_AS(a % b, const std::invalid_argument&);
    }
}

// Constructor
TEST_CASE("Constructor base 10") {
    Constructor<1>();
}

TEST_CASE("Constructor base 100") {
    Constructor<2>();
}

TEST_CASE("Constructor base 1000") {
    Constructor<3>();
}

TEST_CASE("Constructor base 10000") {
    Constructor<4>();
}

TEST_CASE("Constructor base 100000") {
    Constructor<5>();
}

TEST_CASE("Constructor base 1000000") {
    Constructor<6>();
}

TEST_CASE("Constructor base 10000000") {
    Constructor<7>();
}

TEST_CASE("Constructor base 100000000") {
    Constructor<8>();
}

TEST_CASE("Constructor base 1000000000") {
    Constructor<9>();
}

// Comparison operators
TEST_CASE("Comparison operators base 10") {
    ComparisonOperators<1>();
}

TEST_CASE("Comparison operators base 100") {
    ComparisonOperators<2>();
}

TEST_CASE("Comparison operators base 1000") {
    ComparisonOperators<3>();
}

TEST_CASE("Comparison operators base 10000") {
    ComparisonOperators<4>();
}

TEST_CASE("Comparison operators base 100000") {
    ComparisonOperators<5>();
}

TEST_CASE("Comparison operators base 1000000") {
    ComparisonOperators<6>();
}

TEST_CASE("Comparison operators base 10000000") {
    ComparisonOperators<7>();
}

TEST_CASE("Comparison operators base 100000000") {
    ComparisonOperators<8>();
}

TEST_CASE("Comparison operators base 1000000000") {
    ComparisonOperators<9>();
}

// Arithmetic operators
TEST_CASE("Arithmetic operations base 10") {
    ArithmeticOperators<1>();
}

TEST_CASE("Arithmetic operations base 100") {
    ArithmeticOperators<2>();
}

TEST_CASE("Arithmetic operations base 1000") {
    ArithmeticOperators<3>();
}

TEST_CASE("Arithmetic operations base 10000") {
    ArithmeticOperators<4>();
}

TEST_CASE("Arithmetic operations base 100000") {
    ArithmeticOperators<5>();
}

TEST_CASE("Arithmetic operations base 1000000") {
    ArithmeticOperators<6>();
}

TEST_CASE("Arithmetic operations base 10000000") {
    ArithmeticOperators<7>();
}

TEST_CASE("Arithmetic operations base 100000000") {
    ArithmeticOperators<8>();
}

TEST_CASE("Arithmetic operations base 1000000000") {
    ArithmeticOperators<9>();
}

// Long arithmetic operators
TEST_CASE("Long arithmetic operations base 10") {
    LongArithmeticOperators<1>();
}

TEST_CASE("Long arithmetic operations base 100") {
    LongArithmeticOperators<2>();
}

TEST_CASE("Long arithmetic operations base 1000") {
    LongArithmeticOperators<3>();
}

TEST_CASE("Long arithmetic operations base 10000") {
    LongArithmeticOperators<4>();
}

TEST_CASE("Long arithmetic operations base 100000") {
    LongArithmeticOperators<5>();
}

TEST_CASE("Long arithmetic operations base 1000000") {
    LongArithmeticOperators<6>();
}

TEST_CASE("Long arithmetic operations base 10000000") {
    LongArithmeticOperators<7>();
}

TEST_CASE("Long arithmetic operations base 100000000") {
    LongArithmeticOperators<8>();
}

TEST_CASE("Long arithmetic operations base 1000000000") {
    LongArithmeticOperators<9>();
}