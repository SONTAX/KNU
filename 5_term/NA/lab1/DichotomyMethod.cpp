#include "DichotomyMethod.h"

long double DichotomyMethod::calculateResult() {
    a = function.getA();
    b = function.getB();
    eps = function.getEps();
    long double c;
    while ((std::abs(b - a)) > eps) {
        c = a + (b - a) / 2;
        if ((function.calculateFunction(a) * function.calculateFunction(c)) < 0) {
            b = c;
        } else if ((function.calculateFunction(b) * function.calculateFunction(c)) < 0) {
            a = c;
        } else if (function.calculateFunction(c) == 0.0) {
            return c;
        }
        iterations++;
    }
    return a;
}

void DichotomyMethod::printResult() {
    std::cout << "Dichotomy method result: " << std::fixed << std::setprecision(15) <<
        calculateResult() << "\tIterations: " << iterations << std::endl;
}
