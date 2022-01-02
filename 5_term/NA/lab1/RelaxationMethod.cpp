#include "RelaxationMethod.h"

long double RelaxationMethod::calculateResult() {
    a = function.getA();
    b = function.getB();
    eps = function.getEps();
    long double previous = a + (b - a) / 2;
    long double alpha = calculateAlpha();
    if (function.calculateFunctionInPoint(previous) > 0) {
        alpha *= -1;
    }
    long double x = alpha * function.calculateFunction(previous) + previous;
    while ((std::abs(x - previous) > eps)) {
        previous = x;
        x = alpha * function.calculateFunction(previous) + previous;
        iterations++;
    }
    return x;
}

void RelaxationMethod::printResult() {
    std::cout << "Relaxation method result: " << std::fixed << std::setprecision(15) <<
        calculateResult() << "\tIterations: " << iterations  << std::endl;
}

long double RelaxationMethod::calculateAlpha() {
    a = function.getA();
    b = function.getB();
    long double eps = 1e-3;
    long double M1 = 0;
    long double m1 = 0;
    while (a < b) {
        if (M1 > std::abs(function.calculateFunctionInPoint(a))) {
            M1 = std::abs(function.calculateFunctionInPoint(a));
        }
        if (m1 < std::abs(function.calculateFunctionInPoint(a))) {
            m1 = std::abs(function.calculateFunctionInPoint(a));
        }
        a += eps;
    }
    return 2 / (M1 + m1);
}
