#include <iostream>
#include "CalculatorFaza2.h"
#include "CalculationProcessor.h"

using namespace std;

void CalculatorFaza2::displayVariables() {

    CalculationProcessor calcProcessor;

    cout << "Calculator Variables: " << endl;

    for (int i = 0; i < variablesLength; i++) {
        cout << variables[i] << " = ";

        char* temp = new char[100];
        Helper::doubleToCharArray(variableValue[i], temp, calcProcessor.getNumberPrecision());
        cout << temp << endl;
        delete[] temp;

    }
}

void CalculatorFaza2::replaceVariablesWithValues(char* str) {
    CalculationProcessor calcProcessor;
    for (int i = 0; i < variablesLength; i++) {
        string mainInputAsString(str);
        int pos = mainInputAsString.find(variables[i]);
        if (pos != -1) {
            calcProcessor.replace(str, pos, pos + variables[i].length() - 1, variableValue[i], calcProcessor.getNumberPrecision());
            i = 0;
        }
    }
}

int CalculatorFaza2::checkForSaveVariable(char* str) {

    string command;
    string strAsString(str);
    command = "saveas";

    if (strAsString.substr(0, command.length()) != command)
        return 0;

    if (outputHistoryLength - 1 < 0)
    {
        cout << "No value to save as a variable" << endl;
        return 0;
    }

    string variableName = strAsString.substr(command.length());

    addNewVariableToList(variableName);

    addNewVariableValueToList(outputHistory[outputHistoryLength - 1]);

    return 1;
}
