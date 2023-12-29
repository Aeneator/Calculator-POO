#pragma once
#include <iostream>
using namespace std;

class Helper {
public:
	static bool isThisCharPartOfNumber(char c) {
        return strchr("1234567890.", c) != NULL;
    }

    static double charArrayToDouble(char* charArray) {
        if (charArray != nullptr && strcmp(charArray, "") != 0)
            return stod(charArray);
        else return 0;
    }

    static void doubleToCharArray(double doubleValue, char* charArray, int numberPrecision) {
        char precision[20];
        sprintf_s(precision, sizeof(precision), "%%.%dlf",10);

        sprintf_s(charArray, Calculator::getMaxInputSize(), precision, doubleValue);

        if (strchr(charArray, '.') != NULL) {
            int i = strlen(charArray) - 1;
            while ( charArray[i] == '0') {
                charArray[i] = '\0';
                i--;
            }
            if (charArray[i] == '.')
                charArray[i] = '\0';
        }
    }
};