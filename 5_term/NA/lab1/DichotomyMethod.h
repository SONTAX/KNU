#ifndef LAB1_DICHOTOMY_METHOD_H
#define LAB1_DICHOTOMY_METHOD_H

#include "TestFunction.h"

class DichotomyMethod {
private:
    TestFunction function;
    long long iterations = 1;
    long double a;
    long double b;
    long double eps;
    long double calculateResult();
public:
    void printResult();
};

#endif //LAB1_DICHOTOMY_METHOD_H
