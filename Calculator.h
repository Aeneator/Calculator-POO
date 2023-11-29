#pragma once
#include <iostream>

using namespace std;

class Calculator {
private:
    char* mainInput;
    static const int maxInputSize = 100;
    static bool validInputFlag;

    char** inputHistory;
    int inputHistoryEntries = 0;
    double* outputHistory;
    int outputHistoryLength;

    void trimInput(char* input) {
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

    void processNewInput() {
        if (strcmp(mainInput, "exit") == 0)
            return;
        Calculator::setValidInputFlag(isInputValid(mainInput));
        
        if (!getValidInputFlag()) {
            return;
        }

        trimInput(mainInput);

        // add the input to history
        addNewInputHistoryEntry(mainInput);

        if (isPolinomial(mainInput))
            calculatePolinomial();
        else
            calculate();
    }

    void addNewInputHistoryEntry(char* newInput) {
        if (inputHistory == nullptr || inputHistoryEntries <= 0) {
            inputHistoryEntries = 1;
            inputHistory = new char* [inputHistoryEntries];
            inputHistory[0] = new char[strlen(newInput) + 1];
            strcpy_s(inputHistory[0], strlen(newInput) + 1, newInput);
        }
        else {
            char** inputCopies = new char* [inputHistoryEntries];
            for (int i = 0; i < inputHistoryEntries; i++) {
                inputCopies[i] = new char[strlen(inputHistory[i]) + 1];
                strcpy_s(inputCopies[i], strlen(inputHistory[i]) + 1, inputHistory[i]);
            }

            for (int i = 0; i < inputHistoryEntries; i++)
                delete[] inputHistory[i];
            delete[] inputHistory;

            inputHistoryEntries++;
            inputHistory = new char* [inputHistoryEntries];
            for (int i = 0; i < inputHistoryEntries - 1; i++) {
                inputHistory[i] = new char[strlen(inputCopies[i]) + 1];
                strcpy_s(inputHistory[i], strlen(inputCopies[i]) + 1, inputCopies[i]);
            }
            inputHistory[inputHistoryEntries - 1] = new char[strlen(newInput) + 1];
            strcpy_s(inputHistory[inputHistoryEntries - 1], strlen(newInput) + 1, newInput);

            for (int i = 0; i < inputHistoryEntries - 1; i++)
                delete[] inputCopies[i];
            delete[] inputCopies;
            
        }
    }

    void addNewOutputHistoryEntry(double newOutput) {
        if (!Calculator::getValidInputFlag())
            newOutput = 0;
        if (outputHistory == nullptr || outputHistoryLength <= 0) {
            outputHistoryLength = 1;
            outputHistory = new double[1];
            outputHistory[0] = newOutput;
        }
        else {
            float* outputCopies = new float[outputHistoryLength];

            for (int i = 0; i < outputHistoryLength; i++)
                outputCopies[i] = outputHistory[i];

            delete[] outputHistory;
            
            outputHistoryLength++;

            outputHistory = new double[outputHistoryLength];

            for (int i = 0; i < outputHistoryLength - 1; i++) {
                outputHistory[i] = outputCopies[i];
            }

            outputHistory[outputHistoryLength - 1] = newOutput;

            delete[] outputCopies;
        }
    }

    bool isInputValid(char* input) {
        char validCharacters[] = { '1','2','3','4','5','6','7','8','9','0','(',')','[',']','-','+','*','/','#','^','.','x','X','=',' ','\0'};
        for (int i = 0; i < strlen(input); i++)
            if (strchr(validCharacters, input[i]) == NULL)
                return false;

        return true;
    }
    void calculate();
    void calculatePolinomial();

    bool isPolinomial(char* input) {
        char polinomialSignature[] = { 'x','=','\0'};
        int count = 0;
        for (int i = 0; i < strlen(input); i++)
            if (strchr(polinomialSignature, input[i]) != NULL)
                count++;
        if (count >= 2)
            return true;
        else
            return false;
    }

public:

    Calculator() {
        validInputFlag = true;
        mainInput = new char[maxInputSize];
        strcpy_s(mainInput, 2, "0");

        inputHistory = nullptr;
        outputHistory = nullptr;

        inputHistoryEntries = 0;
        outputHistoryLength = 0;
    }

    Calculator(const char* input) : Calculator() {
        if (input != NULL)
        {
            strcpy_s(mainInput, 100, input);
            processNewInput();
        }
    }

    Calculator(Calculator& obj) {
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
    }
    
    ~Calculator() {
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
        
    }

    friend ostream& operator<<(ostream& out, Calculator obj) {
        if (Calculator::getValidInputFlag()) {
            if (strcmp(obj.mainInput, "0") != 0)
                out << "Result: " << obj.mainInput;
            else
                out << "Result: 0";
        }
        else {
            strcpy_s(obj.mainInput, obj.maxInputSize, "Input was not valid.");
            out << obj.mainInput;
        }
        return out;
    }

    friend istream& operator>>(istream& in, Calculator& obj) {
        in.getline(obj.mainInput, obj.maxInputSize);
        obj.processNewInput();
        return in;
    }

    Calculator& operator=(const Calculator& obj) {
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
                for (int i = 0; i < inputHistoryEntries; i++) {
                    inputHistory[i] = new char[strlen(obj.inputHistory[i]) + 1];
                    strcpy_s(inputHistory[i], strlen(obj.inputHistory[i]) + 1, obj.inputHistory[i]);
                }
            }
            if (obj.outputHistory != nullptr) {
                if (outputHistory != nullptr)
                    delete[] outputHistory;
                
                outputHistory = new double[obj.outputHistoryLength];
                for (int i = 0; i < obj.outputHistoryLength; i++) {
                    outputHistory[i] = obj.outputHistory[i];
                }
            }
        }
        return *this;
    }

    // Operator overloading for += (char[])
    Calculator& operator+=(const char* str) {
        if (getValidInputFlag()) {
            strcat_s(mainInput, maxInputSize, "+(");
            strcat_s(mainInput, maxInputSize, str);
            strcat_s(mainInput, maxInputSize, ")");
            processNewInput();
        }
        return *this;
    }

    // Operator overloading for ==
    bool operator==(const Calculator& other) {
        return strcmp(this->mainInput, other.mainInput) == 0;
    }

    char* getMainInput() {
        return mainInput;
    }

    void readInput() {
        if (mainInput != nullptr)
            delete[] mainInput;
        mainInput = new char[maxInputSize];
        
        cin.getline(mainInput, maxInputSize);
        processNewInput();
    }

    void readInput(const char* input) {
        if (mainInput != nullptr)
            delete[] mainInput;
        mainInput = new char[maxInputSize];

        strcpy_s(mainInput, strlen(input) + 1, input);

        processNewInput();
    }

    static const int getMaxInputSize() {
        return maxInputSize;
    }

    static bool getValidInputFlag() {
        return validInputFlag;
    }

    static void setValidInputFlag(bool value) {
        validInputFlag = value;
    }

    void displayHistory();

};
