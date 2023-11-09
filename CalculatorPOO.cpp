#include <iostream>
#include "Calculator.h"

using namespace std;

void TestTastatura() {
    Calculator calc;

    cin >> calc;

    while (strcmp(calc.getMainInput(), "exit") != 0) {

        cout << calc << endl;

        cin >> calc;
    }
}

void TestPredefinit() {
    
    cout << "Exemple de teste din word: " << endl << endl;
    Calculator c1("[40 + (5 - 1)] * 2");
    cout << c1 << endl;
    cout << "Expected: 88" << endl;
    Calculator c2("5 / 0 ");
    cout << c2 << endl;
    cout << "Expected: error, can't divide by 0" << endl;
    Calculator c3("[(2 * 3) ^ 2] / 4 - (6 + 2)#3");
    cout << c3 << endl;
    cout << "Expected: 7" << endl;
    Calculator c4("2 * 3.2");
    cout << c4 << endl;
    cout << "Expected: 6.4" << endl;
    Calculator c5("24342343.0002 - 3");
    cout << c5 << endl;
    cout << "Expected: 24342340.0002" << endl;
    Calculator c6("2 * 3 - 8");
    cout << c6 << endl;
    cout << "Expected: -2" << endl;

    cout << "\nTeste personale pentru edge case-uri: " << endl << endl;
    Calculator c7("-8-10");
    cout << c7 << endl;
    cout << "Expected: -18" << endl;
    Calculator c8("2--2");
    cout << c8 << endl;
    cout << "Expected: 4" << endl;
    Calculator c9("(-1)*9");
    cout << c9 << endl;
    cout << "Expected: -9" << endl;
    Calculator c10("(-1)*(-11)");
    cout << c10 << endl;
    cout << "Expected: 11" << endl;
    Calculator c11("8*(-1)");
    cout << c11 << endl;
    cout << "Expected: -8" << endl;
    Calculator c12("20*-1");
    cout << c12 << endl;
    cout << "Expected: -20" << endl;
    Calculator c13("2^(-5)");
    cout << c13 << endl;
    cout << "Expected: 0.0312" << endl;
    Calculator c14("(-1)^(-1)");
    cout << c14 << endl;
    cout << "Expected: -1" << endl;
    Calculator c15("-5--1");
    cout << c15 << endl;
    cout << "Expected: -4" << endl;
    
}

void TestObiect() {
    // Test constructor implicit
    Calculator c1;
    cout << c1 << endl;
    cout << "Expected: 0" << endl;
    // Test constructor cu parametru
    Calculator c2("2/7");
    cout << c2 << endl;
    cout << "Expected: 0.28571" << endl;
    // Test constructor copiere
    Calculator c3(c2);
    cout << c3 << endl;
    cout << "Expected: 0.28571" << endl;
    // Test Operator Incrementare
    Calculator c4("5");
    c4 += "2";
    cout << c4 << endl;
    cout << "Expected: 7" << endl;
    // Test operator egal
    Calculator c5;
    c5 = c2;
    cout << c5 << endl;
    cout << "Expected: 0.28571" << endl;
  
}

int main()
{
   
    TestObiect();

    return 0;
}

/*
Ways to read into the class:
Constructors, requires memory
readInput(),
+= operator,
= operator
*/
