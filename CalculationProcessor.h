#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "Operations.h"
#include "Helper.h"

using namespace std;

class CalculationProcessor {
private:
    int numberPrecision;
    void calculateSingleOperation(const char operationSymbol, char* str) {

        Operations op;
     
        for (int i = 0; i < strlen(str); i++) {
            if (operationSymbol == str[i]) {

                // selects the number left to the found symbol
                char* leftNum = new char[Calculator::getMaxInputSize()];
                int leftNumIndex;
                selectNumberToTheLeft(str, leftNum, i, leftNumIndex);

                // selects the number right to the found symbol
                char* rightNum = new char[Calculator::getMaxInputSize()];
                int rightNumIndex;
                selectNumberToTheRight(str, rightNum, i, rightNumIndex);

                // calculates the result of the operation between the right and left numbers of the symbol
                double result;
                bool resultFound = false;
                switch (operationSymbol) {
                case '#': 
                    result = op.root(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum)); resultFound = true; break;
                case '^': result = op.power(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum)); resultFound = true; break;
                case '*': result = op.multiplication(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum)); resultFound = true; break;
                case '/': result = op.division(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum)); resultFound = true; break;
                case '+': 
                    if (i - 1 >= 0 && Helper::isThisCharPartOfNumber(str[i - 1])) {
                        result = op.addition(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum));
                        resultFound = true;
                    }
                    break;
                case '-':
                    if (i - 1 >= 0 && Helper::isThisCharPartOfNumber(str[i - 1]) ) {
                        result = op.subtraction(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum));
                        resultFound = true;
                    }
                    break;
                }

                delete[] leftNum;
                delete[] rightNum;

                if (!resultFound)
                    continue;

                // replaces the numbers and symbol with the result
                replace(str, leftNumIndex, rightNumIndex, result, numberPrecision);
                i = leftNumIndex;
            }
            solveMultipleSignProblems(str);
        }
    }

    void selectNumberToTheLeft(char* str, char* result, int pivot, int& leftIndex) {
        leftIndex = 0;

        int resultLength = 0;
        for (int i = pivot - 1; i >= 0; i--) {
            if ((str[i] == '-'|| str[i] == '+') && (i == 0 || !Helper::isThisCharPartOfNumber(str[i - 1]))) {
                result[resultLength++] = str[i];
                continue;
            }
            if (Helper::isThisCharPartOfNumber(str[i]))
                result[resultLength++] = str[i];
            else {
                leftIndex = i + 1;
                break;
            }
        }
        result[resultLength] = '\0';

        //reverse the number
        for (int i = 0; i < resultLength / 2; i++)
            swap(result[i], result[resultLength - 1 - i]);
    }

    void selectNumberToTheRight(char* str, char* result, int pivot, int& rightIndex) {
        rightIndex = strlen(str) - 1;

        int resultLength = 0;
        if (str[pivot + 1] == '-' || str[pivot + 1] == '+') {
            result[resultLength++] = str[pivot + 1];
            pivot++;
        }
        for (int i = pivot + 1; i < strlen(str); i++) {
            if (Helper::isThisCharPartOfNumber(str[i]))
                result[resultLength++] = str[i];
            else {
                rightIndex = i - 1;
                break;
            }
        }
        result[resultLength] = '\0';
    }

    void solveMultipleSignProblems(char* str) {
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == '-') {
                if (str[i + 1] == '-')
                    replateAtAndDeleteNext(str, i, '+');
                if (str[i + 1] == '+')
                    replateAtAndDeleteNext(str, i, '-');
            }
            if (str[i] == '+') {
                if (str[i + 1] == '-')
                    replateAtAndDeleteNext(str, i, '-');
                if (str[i + 1] == '+')
                    replateAtAndDeleteNext(str, i, '+');
            }
        }
    }

    void replateAtAndDeleteNext(char* str, int index, char replacement) {
        int length = strlen(str);
        str[index] = replacement;
        for (int i = index + 1; i < length - 1; i++)
            str[i] = str[i + 1];
        str[length - 1] = '\0';
    }

public:
    CalculationProcessor() {
        setNumberPrecision(5);
    }
    CalculationProcessor(int _numberPrecision) {
        setNumberPrecision(_numberPrecision);
    }
    ~CalculationProcessor(){}

    friend istream& operator>>(istream& in, CalculationProcessor& obj) {
        in >> obj.numberPrecision;
        return in;
    }

    friend ostream& operator<<(ostream& out, CalculationProcessor obj) {
        out << obj.numberPrecision;
        return out;
    }

    bool operator!() {
        return numberPrecision <= 0;
    }
    bool operator>(CalculationProcessor& obj) {
        return numberPrecision > obj.numberPrecision;
    }
    bool operator>=(CalculationProcessor& obj) {
        return numberPrecision >= obj.numberPrecision;
    }
    bool operator<(CalculationProcessor& obj) {
        return numberPrecision < obj.numberPrecision;
    }
    bool operator<=(CalculationProcessor& obj) {
        return numberPrecision <= obj.numberPrecision;
    }
    bool operator==(CalculationProcessor& obj) {
        return numberPrecision == obj.numberPrecision;
    }
    bool operator!=(CalculationProcessor & obj) {
        return numberPrecision == obj.numberPrecision;
    }

    int getNumberPrecision() {
        return numberPrecision;
    }

    void setNumberPrecision(int value) {
        numberPrecision = value;
    }

    void insideParenthesis(char* input, char* selection, int& lastOpenParenthesis, int& firstClosedParanthesis) {

        // get the position of the last open parenthesis
        for (int i = 0; i < strlen(input); i++)
            if (strchr("([", input[i]) != NULL)
                lastOpenParenthesis = i;

        // get the position of the first closed parenthesis
        for (int i = lastOpenParenthesis; i < strlen(input); i++)
            if (strchr(")]", input[i]) != NULL) {
                firstClosedParanthesis = i;
                break;
            }

        // select everything inside the parenthesis
        int j = 0;
        for (int i = lastOpenParenthesis + 1; i <= firstClosedParanthesis - 1; i++)
            selection[j++] = input[i];
        
        selection[j] = '\0'; 
    }

    void solveInOrder(char* str) {
        solveMultipleSignProblems(str);

        calculateSingleOperation('^', str);
        calculateSingleOperation('#', str);
        calculateSingleOperation('/', str);
        calculateSingleOperation('*', str);
        calculateSingleOperation('+', str);
        calculateSingleOperation('-', str);
    }

    void replace(char* str, int start, int end, double replacement, int precision) {

        // select everything left of 'start'
        char* head = new char[start + 1];
        for (int i = 0; i < start; i++)
            head[i] = str[i];
        head[start] = '\0';


        char* replacementCast = new char[Calculator::getMaxInputSize()];
        Helper::doubleToCharArray(replacement, replacementCast,precision);

        // select everything right of 'end'
        char* tail = new char[strlen(str) - end];
        int tailLen = 0;
        for (int i = end + 1; i < strlen(str); i++)
            tail[tailLen++] = str[i];
        tail[tailLen] = '\0';

        // Clear the char array
        for (int i = 0; i < strlen(str); i++)
            str[i] = '\0';

        // combine the 'head', 'replacement' and 'tail' in order
        strcat_s(str, Calculator::getMaxInputSize(), head);
        strcat_s(str, Calculator::getMaxInputSize(), replacementCast);
        strcat_s(str, Calculator::getMaxInputSize(), tail);

        delete[] head;
        delete[] replacementCast;
        delete[] tail;
    }
};