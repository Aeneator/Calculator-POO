#pragma once
#include <iostream>
#include <string>
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
        sprintf_s(precision, sizeof(precision), "%%.%dlf",numberPrecision);

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

    static char* charsubstr(char* arr, int begin, int len)
    {
        char* res = new char[len + 1];
        for (int i = 0; i < len; i++)
            res[i] = *(arr + begin + i);
        res[len] = 0;
        return res;
    }
};