#include "DichotomyMethod.h"
#include "RelaxationMethod.h"
#include "NewtonMethod.h"

int main() {
    DichotomyMethod first;
    RelaxationMethod second;
    NewtonMethod third;
    first.printResult();
    second.printResult();
    third.printResult();
    return 0;
}
