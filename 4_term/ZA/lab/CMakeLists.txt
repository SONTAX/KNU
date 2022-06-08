cmake_minimum_required(VERSION 3.19)
project(lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab main.cpp PolynomialFactoring.hpp LongNumber.hpp LongNumber.inl LongArithmetic.hpp LongArithmetic.inl LongNumberCell.hpp IntegralInfo.hpp EulerFunction.hpp CarmichaelFunction.hpp)