#include <doctest/doctest.h>

#include <GeneralAlgebra/EllipticCurve.hpp>

template <typename T>
void Operations() {
    using EllipticCurve = GeneralAlgebra::EllipticCurve<T>;

    EllipticCurve ellipticCurve(T(1), T(0), T(13));

    SUBCASE("GetInverse") {
        T p1_1x(6);
        T p1_1y(1);
        T p2_1x(5);
        T p2_1y(0);

        auto [x1,y1] = ellipticCurve.GetInverse({ p1_1x, p1_1y });
        auto [x2,y2] = ellipticCurve.GetInverse({ p2_1x, p2_1y });
        auto [x3,y3] = ellipticCurve.GetInverse({ p2_1x, p2_1y });

        CHECK(x1 == T(6));
        CHECK(y1 == T(12));
        CHECK(x2 == T(5));
        CHECK(y2 == T(0));
    }

    SUBCASE("Add") {
        T p1_1x(2);
        T p1_1y(6);
        T p2_1x(3);
        T p2_1y(2);
        T p1_2x(11);
        T p1_2y(9);
        T p1_3x(5);

        auto [x1, y1] = ellipticCurve.Add({ p1_1x, p1_1y                }, { p2_1x, p2_1y                });
        auto [x2, y2] = ellipticCurve.Add({ p1_2x, p1_2y                }, { p1_2x, p1_2y                });
        auto [x3, y3] = ellipticCurve.Add({ p2_1x, p1_2x                }, { p2_1x, p1_1x                });
        auto [x4, y4] = ellipticCurve.Add({ p1_3x, ellipticCurve.GetB() }, { p1_3x, ellipticCurve.GetB() });
        auto [x5, y5] = ellipticCurve.Add({ p1_1x, ellipticCurve.GetA() }, { p1_1x, ellipticCurve.GetA() });

        CHECK(x1 == T(11));
        CHECK(y1 == T(4));
        CHECK(x2 == T(4));
        CHECK(y2 == T(4));
        CHECK(x3 == T(-1));
        CHECK(y3 == T(-1));
        CHECK(x4 == T(-1));
        CHECK(y4 == T(-1));
        CHECK(x5 == T(-1));
        CHECK(y5 == T(-1));
    }
}

TEST_CASE("Operations base 10") {
    Operations<GeneralAlgebra::LongNumber1>();
}

TEST_CASE("Operations base 100") {
    Operations<GeneralAlgebra::LongNumber2>();
}

TEST_CASE("Operations base 1000") {
    Operations<GeneralAlgebra::LongNumber3>();
}

TEST_CASE("Operations base 10000") {
    Operations<GeneralAlgebra::LongNumber4>();
}

TEST_CASE("Operations base 100000") {
    Operations<GeneralAlgebra::LongNumber5>();
}

TEST_CASE("Operations base 1000000") {
    Operations<GeneralAlgebra::LongNumber6>();
}

TEST_CASE("Operations base 10000000") {
    Operations<GeneralAlgebra::LongNumber7>();
}

TEST_CASE("Operations base 100000000") {
    Operations<GeneralAlgebra::LongNumber8>();
}

TEST_CASE("Operations base 1000000000") {
    Operations<GeneralAlgebra::LongNumber9>();
}