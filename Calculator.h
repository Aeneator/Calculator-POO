#pragma once
#include <iostream>
#include "CalculationProcessor.h"
using namespace std;

class Calculator {
private:
    char* mainInput;
    static const int maxInputSize = 100;
    static bool validInputFlag;

    // check if input is valid
    bool isInputValid(char*);
    // remove all spaces from the input
    void trimInput(char*);
    // execute on newInput
    void processNewInput();

public:
    Calculator();

    Calculator(const char* input);

    Calculator(const char* input, int precision);
    Calculator(Calculator& obj);

    ~Calculator();

    friend ostream& operator<<(ostream& os, const Calculator& obj);

    friend istream& operator>>(istream& is, Calculator& obj);

    // Operator overloading for += (char[])
    Calculator& operator+=(const char* str);

    // Operator overloading for ==
    bool operator==(const Calculator& other);

    // Returns the main input
    char* getMainInput();
    // Returns the MaxInputSize
    static const int getMaxInputSize();
    // Get 'ValidInputFlag'
    static bool getValidInputFlag();
    // Set 'ValidInputFlag'
    static void setValidInputFlag(bool);
    // returns the precision of the calculations
    int getCalculationPrecision();
    // sets the precision of the calculations
    void setCalculationPrecision(const int newPrecision);
    // Calculate the result of 'mainInput'
    void calculate();
    // Reads the input
    void readInput();

};