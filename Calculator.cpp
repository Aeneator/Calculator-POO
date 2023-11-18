#include "Calculator.h"
#include "CalculationProcessor.h"
#include "Polinomials.h"

bool Calculator::validInputFlag = true;

void Calculator::calculate() {
    if (!getValidInputFlag()) {
        strcpy_s(getMainInput(), getMaxInputSize(), "Input is not valid.");
        return;
    }

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
        calcProcessor.replace(getMainInput(), firstParenthesis, lastParenthesis, calcProcessor.charArrayToDouble(result));
        // check if the input has parenthesis
        parenthesisFound = (strchr(getMainInput(), '(') != NULL || strchr(getMainInput(), ')') != NULL || strchr(getMainInput(), '[') != NULL || strchr(getMainInput(), ']') != NULL);
    }
    // solve what the remaining operations after there are no parenthesis
    calcProcessor.solveInOrder(getMainInput());
}

void Calculator::calculatePolinomial() {
    if (!getValidInputFlag()) {
        strcpy_s(getMainInput(), getMaxInputSize(), "Input is not valid.");
        return;
    }
    cout << "This is a polinomial" << endl;
    Polinomials polinom;
    
    int foundEqual = -1;

    for (int i = 0; i < strlen(getMainInput()); i++)
        if (getMainInput()[i] == '=')
            foundEqual = i;

    char partAfterPlus[100]; partAfterPlus[0] = '\0';
    strcpy_s(partAfterPlus, 100, getMainInput()+foundEqual+1);
    cout <<"Before simplify: " << partAfterPlus << endl;
    polinom.simplify(partAfterPlus);
    cout <<"After Simplify:  "<< partAfterPlus << endl;
    //polinom.moveFromRightToLeft(getMainInput());

    //polinom.solveWithX(getMainInput());
}