#pragma once
#include <iostream>

using namespace std;

class Calculator {
private:
    char* mainInput;
    static const int maxInputSize = 100;
    static bool validInputFlag;

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
        if (strcmp(getMainInput(), "exit") == 0)
            return;
        Calculator::setValidInputFlag(isInputValid(getMainInput()));
        trimInput(getMainInput());

        if (isPolinomial(mainInput))
            calculatePolinomial();
        else
            calculate();
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
        strcpy_s(mainInput, getMaxInputSize(), "0");
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
           mainInput = new char[getMaxInputSize()];
           strcpy_s(mainInput, getMaxInputSize(), obj.mainInput);
       }
    }
    
    ~Calculator() {
        if (mainInput != nullptr)
            delete[] mainInput;
    }

    friend ostream& operator<<(ostream& out, Calculator obj) {
        out << "Result: "<< obj.mainInput;
        return out;
    }

    friend istream& operator>>(istream& is, Calculator& obj) {
        is.getline(obj.mainInput, obj.getMaxInputSize());
        obj.processNewInput();
        return is;
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
        }
        return *this;
    }

    // Operator overloading for += (char[])
    Calculator& operator+=(const char* str) {
        strcat_s(mainInput, getMaxInputSize(), "+(");
        strcat_s(mainInput, getMaxInputSize(), str);
        strcat_s(mainInput, getMaxInputSize(), ")");
        processNewInput();
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
        
        cin.getline(mainInput, Calculator::getMaxInputSize());
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

};
