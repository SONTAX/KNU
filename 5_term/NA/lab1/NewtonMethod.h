#ifndef LAB1_NEWTON_METHOD_H
#define LAB1_NEWTON_METHOD_H

#include "TestFunction.h"

class NewtonMethod {
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

#endif //LAB1_NEWTON_METHOD_H
