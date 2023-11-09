#pragma once
#include <iostream>
#include <cmath>
#include "Operations.h"
#include "Calculator.h"

using namespace std;

class Operations {
public:

    double subtraction(double x, double y) {
        return x - y;
    }

    double addition(double x, double y) {
        return x + y;
    }

    double root(double x, double y) {
        return pow(x, 1.0 / y);
    }

    double power(double x, double y) {
        return pow(x, y);
    }

    double multiplication(double x, double y) {
        return x * y;
    }

    double division(double dividend, double divisor) {
        if (divisor == 0)
        {
            Calculator::setValidInputFlag(false);
            cout << "Error: can not divide by 0." << endl;
            return NULL;
        }
        return dividend / divisor;
    }

};