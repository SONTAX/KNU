#include "NewtonMethod.h"

long double NewtonMethod::calculateResult() {
    a = function.getA();
    b = function.getB();
    eps = function.getEps();
    long double previous = a + (b - a) / 2;
    long double x = previous - function.calculateFunction(previous)/function.calculateFunctionInPoint(previous);
    while ((std::abs(x - previous) > eps)) {
        previous = x;
        x = previous - function.calculateFunction(previous)/function.calculateFunctionInPoint(previous);
        iterations++;
    }
    return x;
}

void NewtonMethod::printResult() {
    std::cout << "Newton's method result: " << std::fixed << std::setprecision(15) <<
        calculateResult() << "\tIterations: " << iterations << std::endl;
}