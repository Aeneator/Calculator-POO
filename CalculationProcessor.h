#pragma once
#include <iostream>

class CalculationProcessor {
public:
    CalculationProcessor(){}
    ~CalculationProcessor(){}
    CalculationProcessor(CalculationProcessor& calcProcessor) {
        this->numberPrecision = calcProcessor.numberPrecision;
    }

    // return the number precision
    static int getNumberPrecision();

    // set the number precision
    static void setNumberPrecision(int newPrecision);

    // returns into the 'selection' variable the contents of the parenthesis
    void insideParenthesis(char* input, char* selection, int& lastOpenParenthesis, int& firstClosedParanthesis);
    
    // solve the input in order
    void solveInOrder(char*);
    
    // replaces part of a string from index 'start' to index 'end' with the value of 'replacement'
    void replace(char* str, int start, int end, double replacement);

    // transfrom char[] to double
    static double charArrayToDouble(char*);

    // transfrom double to char[]
    static void doubleToCharArray(double doubleValue, char* charArray);

private:
    static int numberPrecision;
    // calculates every operation of the 'operationSymbol' in the given string and modifies it
    void calculateSingleOperation(const char operationSymbol, char* str, int& length);
    
    // select the number to the right of the pivot
    void selectNumberToTheRight(char* str, char* result, int pivot, int& rightIndex);
    
    // select the number to the left of the pivot
    void selectNumberToTheLeft(char* str, char* result, int pivot, int& leftIndex);

    // returns true if the given character is within the list of recognized posible characters of a number
    bool isThisCharPartOfNumber(char c);

};
