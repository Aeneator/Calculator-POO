#pragma once
#include <iostream>
#include <string>
#include "Operations.h"

using namespace std;

class CalculationProcessor {
private:
   

    void calculateSingleOperation(const char operationSymbol, char* str, int& length) {

        Operations op;

        for (int i = 0; i < length; i++) {
            if (operationSymbol == str[i]) {

                // selects the number left to the found symbol
                char leftNum[100]; int leftNumIndex;
                selectNumberToTheLeft(str, leftNum, i, leftNumIndex);

                // selects the number right to the found symbol
                char rightNum[100]; int rightNumIndex;
                selectNumberToTheRight(str, rightNum, i, rightNumIndex);

                // calculates the result of the operation between the right and left numbers of the symbol
                double result = NULL;
                switch (operationSymbol) {
                case '#': result = op.root(charArrayToDouble(leftNum), charArrayToDouble(rightNum)); break;
                case '^': result = op.power(charArrayToDouble(leftNum), charArrayToDouble(rightNum)); break;
                case '*': result = op.multiplication(charArrayToDouble(leftNum), charArrayToDouble(rightNum)); break;
                case '/': result = op.division(charArrayToDouble(leftNum), charArrayToDouble(rightNum)); break;
                case '+': result = op.addition(charArrayToDouble(leftNum), charArrayToDouble(rightNum)); break;
                case '-':
                    if (i - 1 >= 0 && isThisCharPartOfNumber(str[i - 1]) != NULL) {
                        result = op.subtraction(charArrayToDouble(leftNum), charArrayToDouble(rightNum));
                    }
                    break;
                }

                if (result == NULL)
                    continue;

                // replaces the numbers and symbol with the result
                replace(str, leftNumIndex, rightNumIndex, result);
                i = 0;
                length = strlen(str);
            }
        }
    }

    void selectNumberToTheRight(char* str, char* result, int pivot, int& rightIndex) {
        rightIndex = strlen(str) - 1;

        int resultLength = 0;
        if (str[pivot + 1] == '-') {
            result[resultLength++] = str[pivot + 1];
            pivot++;
        }
        for (int i = pivot + 1; i < strlen(str); i++) {
            if (isThisCharPartOfNumber(str[i]))
                result[resultLength++] = str[i];
            else {
                rightIndex = i - 1;
                break;
            }
        }
        result[resultLength] = '\0';
    }

    void selectNumberToTheLeft(char* str, char* result, int pivot, int& leftIndex) {
        leftIndex = 0;

        int resultLength = 0;
        for (int i = pivot - 1; i >= 0; i--) {
            if (str[i] == '-' && (i == 0 || !isThisCharPartOfNumber(str[i - 1]))) {
                result[resultLength++] = str[i];
                continue;
            }
            if (isThisCharPartOfNumber(str[i]))
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

    bool isThisCharPartOfNumber(char c) {
        return strchr("1234567890.", c) != NULL;
    }

    
public:
     static int numberPrecision;
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
        char* select = new char[Calculator::getMaxInputSize()]; int len = 0;
        for (int i = lastOpenParenthesis + 1; i <= firstClosedParanthesis - 1; i++)
            select[len++] = input[i];
        select[len] = '\0';

        // copies insides of the parenthesis into the 'selection' variable
        strcpy_s(selection, Calculator::getMaxInputSize(), select);
        delete[] select;
    }

    void solveInOrder(char* str) {

        int length = strlen(str);
        calculateSingleOperation('^', str, length);
        calculateSingleOperation('#', str, length);
        calculateSingleOperation('*', str, length);
        calculateSingleOperation('/', str, length);
        calculateSingleOperation('+', str, length);
        calculateSingleOperation('-', str, length);
    }


    void replace(char* str, int start, int end, double replacement) {

        // select everything left of 'start'
        char head[100]; int headLen = 0;
        for (int i = 0; i < start; i++)
            head[headLen++] = str[i];
        head[headLen] = '\0';

        // cast 'replacement' from double to char[]
        char replacementCast[100];
        doubleToCharArray(replacement, replacementCast);

        // select everything right of 'end'
        char tail[100]; int tailLen = 0;
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
    }


    double charArrayToDouble(char* charArray) {
        return stod(charArray);
    }

    void doubleToCharArray(double doubleValue, char* charArray) {
        char precision[10], temp[10]; precision[0] = '\0'; temp[0] = '\0';
        strcat_s(precision, 10, "%.");
        sprintf_s(temp, 10, "%d", numberPrecision);
        strcat_s(precision, 10, temp);
        strcat_s(precision, 10, "lf");

        sprintf_s(charArray, Calculator::getMaxInputSize(), precision, doubleValue);
        for (int i = strlen(charArray) - 1; i >= 0; i--) {
            if (charArray[i] == '0') {
                charArray[i] = '\0';
                continue;
            }
            if (charArray[i] == '.') {
                charArray[i] = '\0';
                break;
            }
            if (charArray[i] != '0')
                break;
        }
    }
};
