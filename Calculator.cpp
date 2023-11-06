#include <iostream>
#include "Calculator.h"
#include "CalculationProcessor.h"

using namespace std;

bool Calculator::validInputFlag = true;

Calculator::Calculator() { 
    mainInput = new char[maxInputSize];
    strcpy_s(mainInput,getMaxInputSize(), "0");
    setCalculationPrecision(2);
}

Calculator::Calculator(const char* input) : Calculator() {
    if (input != NULL)
    {
        strcpy_s(mainInput, 100, input);
        processNewInput();
    }
}
Calculator::Calculator(const char* input, int precision) : Calculator() {
    if (input != NULL)
    {
        strcpy_s(mainInput, 100, input);
        processNewInput();
    }
    setCalculationPrecision(precision);
}
/*
Calculator::Calculator(Calculator& obj) {
    if (obj.getMainInput() != nullptr) {
        mainInput = new char[getMaxInputSize()];
        strcpy_s
        nrNote = s.nrNote;
    }
}
*/
Calculator::~Calculator() {
    if (getMainInput() != NULL)
        delete[] getMainInput();
}

ostream& operator<<(ostream& os, const Calculator& obj) {
    os << "Result: " << obj.mainInput;
    return os;
}

istream& operator>>(istream& is, Calculator& obj) {
    is.getline(obj.mainInput, obj.getMaxInputSize());
    obj.processNewInput();
    return is;
}

// Operator overloading for += (char[])
Calculator& Calculator::operator+=(const char* str) {
    strcat_s(this->mainInput, getMaxInputSize(), "+(");
    strcat_s(this->mainInput, getMaxInputSize(), str);
    strcat_s(this->mainInput, getMaxInputSize(), ")");
    processNewInput();
    return *this;
}

// Operator overloading for ==
bool Calculator::operator==(const Calculator& other) {
    return strcmp(this->mainInput, other.mainInput) == 0;
}

char* Calculator::getMainInput() {
    return mainInput;
}

const int Calculator::getMaxInputSize() {
    return Calculator::maxInputSize;
}

bool Calculator::getValidInputFlag() {
    return validInputFlag;
}

void Calculator::setValidInputFlag(bool value) {
    validInputFlag = value;
}

bool Calculator::isInputValid(char* input) {
    char validCharacters[] = { '1','2','3','4','5','6','7','8','9','0','(',')','[',']','-','+','*','/','#','^','.',' ','\0' };
    for (int i = 0; i < strlen(input); i++)
        if (strchr(validCharacters, input[i]) == NULL)
            return false;

    return true;
}

void Calculator::trimInput(char* input) {
    int inputLength = strlen(input);
    for (int i = 0; i < inputLength; i++) {
        if (input[i] == ' ') {
            for (int j = i; j < inputLength - 1; j++)
                input[j] = input[j + 1];
            inputLength--;
            i--;
        }
    }
    input[inputLength] = '\0';
}

void Calculator::processNewInput() {
    if (strcmp(getMainInput(), "exit") == 0)
        return;
    Calculator::setValidInputFlag(isInputValid(getMainInput()));
    trimInput(getMainInput());
    calculate();
}

int Calculator::getCalculationPrecision() {
    return CalculationProcessor::getNumberPrecision();
}

void Calculator::setCalculationPrecision(const int newPrecision) {
    CalculationProcessor::setNumberPrecision(newPrecision);
}

void Calculator::calculate() {
    if (!getValidInputFlag()) {
        strcpy_s(getMainInput(), getMaxInputSize(), "Input is not valid.");
        return;
    }
    CalculationProcessor op;

    // check if the input has parenthesis
    bool parenthesisFound = (strchr(getMainInput(), '(') != NULL || strchr(getMainInput(), ')') != NULL || strchr(getMainInput(), '[') != NULL || strchr(getMainInput(), ']') != NULL);

    // loop while the input contains parenthesis
    while (parenthesisFound) {
        int firstParenthesis, lastParenthesis;
        char result[100];
        // selects the string that is inside the parenthesis
        op.insideParenthesis(getMainInput(), result, firstParenthesis, lastParenthesis);
        // solves the string inside the parenthesis
        op.solveInOrder(result);
        // replaces the parenthesis with the solution
        op.replace(getMainInput(), firstParenthesis, lastParenthesis, op.charArrayToDouble(result));
        // check if the input has parenthesis
        parenthesisFound = (strchr(getMainInput(), '(') != NULL || strchr(getMainInput(), ')') != NULL || strchr(getMainInput(), '[') != NULL || strchr(getMainInput(), ']') != NULL);
    }
    // solve what the remaining operations after there are no parenthesis
    op.solveInOrder(getMainInput());
}

void Calculator::readInput() {
    cin.getline(mainInput, Calculator::getMaxInputSize());
    processNewInput();
}

