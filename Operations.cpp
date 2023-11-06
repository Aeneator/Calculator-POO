#include <iostream>
#include <cmath>
#include "Operations.h"
#include "Calculator.h"

using namespace std;

double Operations::subtraction(double x, double y) {
    return x - y;
}

double Operations::addition(double x, double y) {
    return x + y;
}

double Operations::root(double x, double y) {
    return pow(x, 1.0 / y);
}

double Operations::power(double x, double y) {
    return pow(x, y);
}

double Operations::multiplication(double x, double y) {
    return x * y;
}

double Operations::division(double dividend, double divisor) {
    if (divisor == 0)
    {
        Calculator::setValidInputFlag(false);
        cout << "Error: can not divide by 0." << endl;
        return NULL;
    }
    return dividend / divisor;
}
