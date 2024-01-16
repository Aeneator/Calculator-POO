#include <iostream>
#include "CalculatorFaza2.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Write \"help\" for Menu screen" << endl;
    CalculatorFaza2 calc;

    if (argc > 1) {

        string temp;

        for (int i = 1; i < argc; ++i) {
            temp += argv[i];
        }

        cout << temp << endl;
        calc.readInput(temp.c_str());
        calc.showResult();
    }

    cin >> calc;

    while (strcmp(calc.getMainInput(), "exit") != 0) {

        calc.showResult();

        cin >> calc;
    }

    return 0;
}
