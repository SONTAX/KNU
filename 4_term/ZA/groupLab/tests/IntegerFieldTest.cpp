#include <doctest/doctest.h>

#include <GeneralAlgebra/IntegerField.hpp>

template <typename T>
void SmallLongNumbersOperations(){
    using Field = GeneralAlgebra::IntegerField<T>;

    Field field(T(29));

    SUBCASE("Basic operations"){
        T a(16);
        T b(17);
        T add      = field.Add(a, b);
        T sub      = field.Sub(a, b);
        T mul      = field.Mul(a, b);
        T inverseA = field.GetInverse(a);
        T inverseB = field.GetInverse(b);
        T div      = field.Div(a, b);

        CHECK(add      == 4);
        CHECK(sub      == 28);
        CHECK(mul      == 11);
        CHECK(inverseA == 20);
        CHECK(inverseB == 12);
        CHECK(div      == 18);
    }

    SUBCASE("Sqrt"){
        T a(111);
        T n(907);

        Field add_field(n);

        auto [q1, q2] = add_field.Sqrt(a);

        CHECK(q1 == T(369));
        CHECK(q2 == T(-369));
    }
}

template <typename T>
void LargeLongNumbersOperations(){
    using Field = GeneralAlgebra::IntegerField<T>;

    Field field(T("4133961804910176266304780279992385078497"));

    SUBCASE("Basic operations"){
        T a("2260771851648055870826654827766197999604");
        T b("6260771851648055870826654827766197999604");
        T add      = field.Add(a, b);
        T sub      = field.Sub(a, b);
        T mul      = field.Mul(a, b);
        T inverseA = field.GetInverse(a);
        T inverseB = field.GetInverse(b);
        T div      = field.Div(a, b);

        CHECK(add.ToString()      == "253620093475759209043749095547625842214");
        CHECK(sub.ToString()      == "133961804910176266304780279992385078497");
        CHECK(mul.ToString()      == "246680313829477676817536198310522858507");
        CHECK(inverseA.ToString() == "353336166172469253701010924584706544779");
        CHECK(inverseB.ToString() == "1414466782186030130665531781225096415520");
        CHECK(div.ToString()      == "1828746336581374241729412092536645739071");
    }
}

// Short Operations
//TEST_CASE("Operations base 'int'") {
    // TODO: Refactor Sqrt to int
//    SmallLongNumbersOperations<int>();
//}

TEST_CASE("Operations base 10") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber1>();
}

TEST_CASE("Operations base 100") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber2>();
}

TEST_CASE("Operations base 1000") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber3>();
}

TEST_CASE("Operations base 10000") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber4>();
}

TEST_CASE("Operations base 100000") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber5>();
}

TEST_CASE("Operations base 1000000") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber6>();
}

TEST_CASE("Operations base 10000000") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber7>();
}

TEST_CASE("Operations base 100000000") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber8>();
}

TEST_CASE("Operations base 1000000000") {
    SmallLongNumbersOperations<GeneralAlgebra::LongNumber9>();
}

// Long Operations
TEST_CASE("Operations base 10") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber1>();
}

TEST_CASE("Operations base 100") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber2>();
}

TEST_CASE("Operations base 1000") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber3>();
}

TEST_CASE("Operations base 10000") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber4>();
}

TEST_CASE("Operations base 100000") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber5>();
}

TEST_CASE("Operations base 1000000") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber6>();
}

TEST_CASE("Operations base 10000000") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber7>();
}

TEST_CASE("Operations base 100000000") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber8>();
}

TEST_CASE("Operations base 1000000000") {
    LargeLongNumbersOperations<GeneralAlgebra::LongNumber9>();
}