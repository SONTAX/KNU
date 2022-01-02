#ifndef LAB1_TEST_FUNCTION_H
#define LAB1_TEST_FUNCTION_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <thread>
#include <chrono>
#include <string>

class TestFunction {
private:
    long double a = -8;
    long double b = 5;
    long double eps = 1e-15;
public:
    long double getA() const;
    long double getB() const;
    long double getEps() const;

    void setA(long double a);
    void setB(long double b);
    void setEps(long double eps);

    long double calculateFunction(long double x);
    long double calculateFunctionInPoint(long double x);
};

#endif //LAB1_TEST_FUNCTION_H
