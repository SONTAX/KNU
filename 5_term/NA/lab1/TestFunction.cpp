#include "TestFunction.h"

long double TestFunction::getA() const {
    return a;
}

void TestFunction::setA(long double a) {
    TestFunction::a = a;
}

long double TestFunction::getB() const {
    return b;
}

void TestFunction::setB(long double b) {
    TestFunction::b = b;
}

long double TestFunction::getEps() const {
    return eps;
}

void TestFunction::setEps(long double eps) {
    TestFunction::eps = eps;
}

long double TestFunction::calculateFunction(long double x) {
    return x * x - 4;
//    return 5 * x * x * x - 2 * x * x * std::sin(x) - (long double) 2 / 5;
//    return 5 * x * x - 5;
//    return x * x * x - x + 1;
//    return std::sin(x);
//    return std::atan(x + 5);
}

long double TestFunction::calculateFunctionInPoint(long double x) {
    return (calculateFunction(x + eps) - calculateFunction(x)) / eps;
}
