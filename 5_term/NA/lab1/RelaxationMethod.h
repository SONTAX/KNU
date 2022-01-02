#ifndef LAB1_RELAXATION_METHOD_H
#define LAB1_RELAXATION_METHOD_H

#include "TestFunction.h"

class RelaxationMethod {
private:
    TestFunction function;
    long long iterations = 1;
    long double a;
    long double b;
    long double eps;
    long double calculateResult();
    long double calculateAlpha();
public:
    void printResult();
};

#endif //LAB1_RELAXATION_METHOD_H
