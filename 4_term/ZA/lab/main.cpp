#include <iostream>

#include "LongNumber.hpp"

int main() {
    using namespace GeneralAlgebra::Literals;

    auto number1 = 23_ln10000_2;
    auto number2 = 5_ln10000_2;

    auto number3 = 124444444444_ln10000_2;

    std::cout << number1 << '\n';
    std::cout << number2 << '\n';
    std::cout << number3 * number3 << '\n';
}