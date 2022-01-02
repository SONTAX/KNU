cmake_minimum_required(VERSION 3.19)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp TestFunction.cpp TestFunction.h DichotomyMethod.cpp DichotomyMethod.h NewtonMethod.cpp NewtonMethod.h RelaxationMethod.cpp RelaxationMethod.h)