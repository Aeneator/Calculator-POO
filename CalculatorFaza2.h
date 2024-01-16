#pragma once
#include "Calculator.h"
#include <vector>

class CalculatorFaza2 : public  Calculator {
private:
    string* variables;
    int variablesLength;
    double* variableValue;
    int variableValueLength;

    string outputMethod;

public:
    CalculatorFaza2() {
        validInputFlag = true;
        commandID = 0;
        mainInput = new char[maxInputSize];
        strcpy_s(mainInput, 2, "0");

        inputHistory = nullptr;
        outputHistory = nullptr;
        variables = nullptr;
        variableValue = nullptr;

        inputHistoryEntries = 0;
        outputHistoryLength = 0;
        variablesLength = 0;
        variableValueLength = 0;

        outputMethod = "console";
    }

    CalculatorFaza2(CalculatorFaza2& obj) {
        commandID = obj.commandID;
        if (obj.getMainInput() != nullptr) {
            mainInput = new char[maxInputSize];
            strcpy_s(mainInput, maxInputSize, obj.mainInput);
        }
        else {
            mainInput = nullptr;
        }

        if (obj.inputHistory != nullptr && obj.inputHistoryEntries > 0) {
            inputHistoryEntries = obj.inputHistoryEntries;
            inputHistory = new char* [obj.inputHistoryEntries];
            for (int i = 0; i < obj.inputHistoryEntries; i++) {
                inputHistory[i] = new char[strlen(obj.inputHistory[i]) + 1];
                strcpy_s(inputHistory[i], strlen(obj.inputHistory[i]) + 1, obj.inputHistory[i]);
            }
        }
        else {
            inputHistoryEntries = 0;
            inputHistory = nullptr;
        }

        if (obj.outputHistory != nullptr) {
            outputHistoryLength = obj.outputHistoryLength;
            outputHistory = new double[obj.outputHistoryLength];
            for (int i = 0; i < obj.outputHistoryLength; i++) {
                outputHistory[i] = obj.outputHistory[i];
            }
        }
        else {
            outputHistoryLength = 0;
            outputHistory = nullptr;
        }

        if (obj.variables != nullptr) {
            variablesLength = obj.variablesLength;
            variables = new string[obj.variablesLength];
            for (int i = 0; i < obj.variablesLength; i++) {
                variables[i] = obj.variables[i];
            }
        }
        else {
            variablesLength = 0;
            variables = nullptr;
        }
        if (obj.variableValue != nullptr) {
            variableValueLength = obj.variableValueLength;
            variableValue = new double[obj.variableValueLength];
            for (int i = 0; i < obj.variableValueLength; i++) {
                variableValue[i] = obj.variableValue[i];
            }
        }
        else {
            variableValueLength = 0;
            variableValue = nullptr;
        }
        outputMethod = obj.outputMethod;
    }
    CalculatorFaza2& operator=(const CalculatorFaza2& obj) {
        if (this != &obj) {
            if (mainInput != nullptr) {
                delete[] mainInput;
            }
            if (obj.mainInput != nullptr) {
                mainInput = new char[obj.getMaxInputSize()];
                strcpy_s(mainInput, obj.getMaxInputSize(), obj.mainInput);
            }
            if (obj.inputHistory != nullptr) {
                if (inputHistory != nullptr) {
                    for (int i = 0; i < inputHistoryEntries; i++) {
                        delete[] inputHistory[i];
                    }
                    delete[] inputHistory;
                }

                inputHistory = new char* [obj.inputHistoryEntries];
                inputHistoryEntries = obj.inputHistoryEntries;
                for (int i = 0; i < obj.inputHistoryEntries; i++) {
                    inputHistory[i] = new char[strlen(obj.inputHistory[i]) + 1];
                    strcpy_s(inputHistory[i], strlen(obj.inputHistory[i]) + 1, obj.inputHistory[i]);
                }
            }
            if (obj.outputHistory != nullptr) {
                if (outputHistory != nullptr)
                    delete[] outputHistory;

                outputHistory = new double[obj.outputHistoryLength];
                outputHistoryLength = obj.outputHistoryLength;
                for (int i = 0; i < obj.outputHistoryLength; i++) {
                    outputHistory[i] = obj.outputHistory[i];
                }
            }
            if (obj.variables != nullptr) {
                if (variables != nullptr)
                    delete[] variables;

                variables = new string[obj.variablesLength];
                variablesLength = obj.variablesLength;
                for (int i = 0; i < obj.variablesLength; i++) {
                    variables[i] = obj.variables[i];
                }
            }

            if (obj.variableValue != nullptr) {
                if (variableValue != nullptr)
                    delete[] variableValue;

                variableValue = new double[obj.variableValueLength];
                variableValueLength = obj.variableValueLength;
                for (int i = 0; i < obj.variableValueLength; i++) {
                    variableValue[i] = obj.variableValue[i];
                }
            }
            outputMethod = obj.outputMethod;
        }
        return *this;
    }

    ~CalculatorFaza2() {
        if (mainInput != nullptr) {
            delete[] mainInput;
            mainInput = nullptr;
        }

        if (inputHistory != nullptr) {
            for (int i = 0; i < inputHistoryEntries; i++) {
                if (inputHistory[i] != nullptr)
                    delete[] inputHistory[i];
            }
            delete[] inputHistory;
            inputHistory = nullptr;
        }

        if (outputHistory != nullptr) {
            delete[] outputHistory;
            outputHistory = nullptr;
        }

        if (variables != nullptr) {
            delete[] variables;
            variables = nullptr;
        }

        if (variableValue != nullptr) {
            delete[] variableValue;
            variableValue = nullptr;
        }

    }

    void showResult() {

        if (outputMethod == "console") {

            if (getValidInputFlag()) {
                if (commandID == 0)
                    cout << mainInput << endl;
            }
            else {
                strcpy_s(mainInput, maxInputSize, "Input was not valid.");
                cout << mainInput << endl;
            }
        }
        else {
            if (getValidInputFlag()) {
                if (commandID == 0) {
                    string prefix = "file ";
                    string fileName = outputMethod.substr(prefix.length());

                    ifstream inputFile(fileName);

                    int lineLength = 0;
                    vector<string> lines;
                    string currentLine;
                    
                    if (inputFile.is_open()) {
                        while (getline(inputFile, currentLine)) {
                            lines.push_back(currentLine);
                            lineLength++;
                        }

                        inputFile.close();
                    }

                    ofstream outputFile(fileName.c_str());

                    if (outputFile.is_open()) {

                        for (int i = 0; i < lineLength; i++)
                            outputFile << lines[i] << endl;

                        outputFile << inputHistory[inputHistoryEntries - 1] << " = " << outputHistory[outputHistoryLength - 1] << endl;

                        outputFile.close();
                    }
                    else {
                        cout << "Error opening the file for writing." << endl;
                    }
                }
            }
            else {
                strcpy_s(mainInput, maxInputSize, "Input was not valid.");
                cout << mainInput << endl;
            }
        }
    }


    void processNewInput() override {

        trimInput(mainInput);

        checkForCommands();

        if (commandID != 0)
            return;

        replaceVariablesWithValues(mainInput);

        Calculator::setValidInputFlag(isInputValid(mainInput));

        if (!getValidInputFlag()) {
            return;
        }

        // add the input to history
        addNewInputHistoryEntry(mainInput);

        calculate();

    }


    void checkForCommands() {
        commandID = 0;

        commandID = checkForSaveVariable(mainInput);

        if (menu.checkForExitCode(mainInput)) {
            commandID = 33;
        }

        if (menu.checkForClearScreen(mainInput)) {
            commandID = 777;
            system("cls");
            cout << "Write \"help\" for Menu screen" << endl;
        }

        if (menu.checkForHelpCode(mainInput)) {
            commandID = 44;
            menu.showHelp(outputMethod);
        }

        if (menu.checkForRemoveVariables(mainInput)) {
            commandID = 56;
            removeAllVariables();
        }

        if (menu.checkForShowVariables(mainInput)) {
            commandID = 55;
            displayVariables();
        }

        if (menu.checkForSaveVariablesToFile(mainInput)) {
            commandID = 60;
            saveToBinaryFile(variables, variablesLength, variableValue, variableValueLength, "DefaultVariablesFile.bin");
        }

        if (menu.checkForLoadVariablesFromFile(mainInput)) {
            commandID = 61;
            readFromBinaryFile("DefaultVariablesFile.bin");
        }

        if (menu.checkForSaveVariablesToFileCustomName(mainInput)) {
            commandID = 62;
            string prefix = "savevariablesto";
            saveToBinaryFile(variables, variablesLength, variableValue, variableValueLength, mainInput + prefix.length());
        }

        if (menu.checkForLoadVariablesFromFileCustomName(mainInput)) {
            commandID = 63;
            string prefix = "loadvariablesfrom";
            readFromBinaryFile(mainInput + prefix.length());
        }

        if (menu.checkForLoadExpressionsFromFile(mainInput)) {
            string prefix = "loadfile";
            loadExpressionsFromFile(mainInput + prefix.length());
            commandID = 90;
        }

        if (menu.checkForHistory(mainInput)) {
            commandID = 101;
            displayHistory();
        }

        if (menu.checkForSaveHistory(mainInput)) {
            commandID = 102;
            saveHistoryToFile();
        }

        if (menu.checkForOutPutMehtodConsole(mainInput)) {
            commandID = 200;
            outputMethod = "console";
            cout << "Current output method: " << outputMethod << endl;
        }

        if (menu.checkForOutPutMehtodFile(mainInput)) {
            commandID = 201;
            string prefix = "outputfile";
            string param = mainInput + prefix.length();

            if (param == "")
                outputMethod = "file defaultOutputFile.txt";
            else
                outputMethod = "file " + param;

            cout << "Current output method: " << outputMethod << endl;
        }

        Calculator::setValidInputFlag(commandID != 0);

    }
    void addNewVariableToList(string newVariable) {
        if (variables == nullptr || variablesLength <= 0) {
            variablesLength = 1;
            variables = new string[1];
            variables[0] = newVariable;
        }
        else {
            for (int i = 0; i < variablesLength; i++) {
                if (newVariable == variables[i]) {
                    for (int j = i; j < variablesLength - 1; j++) {
                        variables[j] = variables[j + 1];
                    }
                    variablesLength--;

                    for (int j = i; j < variableValueLength; j++) {
                        variableValue[j] = variableValue[j + 1];
                    }
                    variableValueLength--;
                }
            }

            string* variableCopies = new string[variablesLength];

            for (int i = 0; i < variablesLength; i++)
                variableCopies[i] = variables[i];

            delete[] variables;

            variablesLength++;

            variables = new string[variablesLength];

            for (int i = 0; i < variablesLength - 1; i++) {
                variables[i] = variableCopies[i];
            }

            variables[variablesLength - 1] = newVariable;

            delete[] variableCopies;
        }
    }

    void addNewVariableValueToList(double newValue) {
        if (!Calculator::getValidInputFlag())
            newValue = 0;
        if (variableValue == nullptr || variableValueLength <= 0) {
            variableValueLength = 1;
            variableValue = new double[1];
            variableValue[0] = newValue;
        }
        else {
            double* variableValueCopies = new double[variableValueLength];

            for (int i = 0; i < variableValueLength; i++)
                variableValueCopies[i] = variableValue[i];

            delete[] variableValue;

            variableValueLength++;

            variableValue = new double[variableValueLength];

            for (int i = 0; i < variableValueLength - 1; i++) {
                variableValue[i] = variableValueCopies[i];
            }

            variableValue[variableValueLength - 1] = newValue;

            delete[] variableValueCopies;
        }
    }

    void removeAllVariables() {

        if (variables != nullptr) {
            delete[] variables;
        }

        if (variableValue != nullptr)
        {
            delete[] variableValue;
        }

        variables = nullptr;
        variableValue = nullptr;

        variablesLength = 0;
        variableValueLength = 0;
    }

    void saveToBinaryFile(const string* variables, int variablesLength, const double* variableValue, int variableValueLength, const string fileName) {

        ofstream file(fileName, ios::binary);

        if (file.is_open()) {

            file.write(reinterpret_cast<const char*>(&variablesLength), sizeof(int));

            for (int i = 0; i < variablesLength; ++i) {
                int variableLength = variables[i].length();
                file.write(reinterpret_cast<const char*>(&variableLength), sizeof(int));
                file.write(variables[i].c_str(), variableLength + 1);
            }

            file.write(reinterpret_cast<const char*>(&variableValueLength), sizeof(int));

            file.write(reinterpret_cast<const char*>(variableValue), variableValueLength * sizeof(double));

            file.close();
            cout << "Data saved to file: " << fileName << endl;
        }
        else {
            cout << "Error opening file for writing." << endl;
        }
    }

    void readFromBinaryFile(const string& fileName) {

        ifstream file(fileName, ios::binary);

        if (file.is_open()) {

            int variablesLengthFile;
            file.read(reinterpret_cast<char*>(&variablesLengthFile), sizeof(int));

            for (int i = 0; i < variablesLengthFile; ++i) {
                int strLength;
                file.read(reinterpret_cast<char*>(&strLength), sizeof(int));

                char* buffer = new char[strLength + 1];
                file.read(buffer, strLength + 1);
                buffer[strLength] = '\0';

                addNewVariableToList(buffer);
                delete[] buffer;
            }

            int variableValueLengthFile;

            file.read(reinterpret_cast<char*>(&variableValueLengthFile), sizeof(int));

            double* variableValueFile = new double[variableValueLengthFile];

            file.read(reinterpret_cast<char*>(variableValueFile), variableValueLengthFile * sizeof(double));

            for (int i = 0; i < variablesLengthFile; i++)
                addNewVariableValueToList(variableValueFile[i]);

            file.close();

            delete[] variableValueFile;

            cout << "Data read from file: " << fileName << endl;
        }
        else {
            cout << "Error opening file for reading." << endl;
        }
    }

    void loadExpressionsFromFile(char* fileName) {

        ifstream inputFile(fileName);

        if (!inputFile.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            readInput(line.c_str());
            if (outputMethod == "console" || getValidInputFlag() == false) {
                if (commandID == 0)
                    cout << line << " = ";
            }
            showResult();
        }

        inputFile.close();
    }

    void displayVariables();
    void saveHistoryToFile();
    int checkForSaveVariable(char* str);
    void replaceVariablesWithValues(char* str);

};