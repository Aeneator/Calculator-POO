#include "Calculator.h"
#include "CalculationProcessor.h"

bool Calculator::validInputFlag = true;

void Calculator::calculate() {

    CalculationProcessor calcProcessor;

    // check if the input has parenthesis
    bool parenthesisFound = (strchr(getMainInput(), '(') != NULL || strchr(getMainInput(), ')') != NULL || strchr(getMainInput(), '[') != NULL || strchr(getMainInput(), ']') != NULL);

    // loop while the input contains parenthesis
    while (parenthesisFound) {
        int firstParenthesis, lastParenthesis;
        char result[100];
        // selects the string that is inside the parenthesis
        calcProcessor.insideParenthesis(getMainInput(), result, firstParenthesis, lastParenthesis);
        // solves the string inside the parenthesis
        calcProcessor.solveInOrder(result);
        // replaces the parenthesis with the solution
        calcProcessor.replace(getMainInput(), firstParenthesis, lastParenthesis, Helper::charArrayToDouble(result),calcProcessor.getNumberPrecision());
        // check if the input has parenthesis
        parenthesisFound = (strchr(getMainInput(), '(') != NULL || strchr(getMainInput(), ')') != NULL || strchr(getMainInput(), '[') != NULL || strchr(getMainInput(), ']') != NULL);
    }
    // solve what the remaining operations after there are no parenthesis
    calcProcessor.solveInOrder(getMainInput());

    if (mainInput[0] == '+') {
        for (int i = 0; i < strlen(mainInput) - 1; i++) {
            mainInput[i] = mainInput[i + 1];
        }
        mainInput[strlen(mainInput) - 1] = '\0';
    }

    if (strcmp(mainInput, "-0") == 0)
        strcpy_s(mainInput, 2, "0");

    addNewOutputHistoryEntry(Helper::charArrayToDouble(mainInput));

}

void Calculator::displayHistory() {

    CalculationProcessor calcProcessor;

    cout << "Calculator History: " << endl;
    
    for (int i = 0; i < inputHistoryEntries; i++) {
        cout << "Input[" << i << "]: " << inputHistory[i] << " = ";
       
        char* temp = new char[maxInputSize];
        Helper::doubleToCharArray(outputHistory[i], temp, calcProcessor.getNumberPrecision());
        cout << temp << endl;
        delete[] temp;
    
    }
}

