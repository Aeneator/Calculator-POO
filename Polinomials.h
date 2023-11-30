#pragma once
#include "CalculationProcessor.h"

/*
void Calculator::calculatePolinomial() {

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
*/
class Polinomials {
private:
	CalculationProcessor calcProcessor;
public:

	void simplify(char* input) {
		// check if the input has parenthesis
		bool parenthesisFound = (strchr(input, '(') != NULL || strchr(input, ')') != NULL || strchr(input, '[') != NULL || strchr(input, ']') != NULL);
		
		// loop while the input contains parenthesis
		while (parenthesisFound) {
			int firstParenthesis, lastParenthesis;
			char result[100];
			// selects the string that is inside the parenthesis
			calcProcessor.insideParenthesis(input, result, firstParenthesis, lastParenthesis);
			// solves the string inside the parenthesis
			// calcProcessor.solveInOrder(result);
			// replaces the parenthesis with the solution
			calcProcessor.replace(input, firstParenthesis, lastParenthesis, Helper::charArrayToDouble(result), calcProcessor.numberPrecision);
			// check if the input has parenthesis
			parenthesisFound = (strchr(input, '(') != NULL || strchr(input, ')') != NULL || strchr(input, '[') != NULL || strchr(input, ']') != NULL);
		}
		// solve what the remaining operations after there are no parenthesis
		calcProcessor.solveInOrder(input);
	}

	void solveInOrder(char* str) {
		calcProcessor.solveMultipleSignProblems(str);
		int length = strlen(str);
		calculateSingleOperation('^', str, length);
		calculateSingleOperation('#', str, length);
		calculateSingleOperation('*', str, length);
		calculateSingleOperation('/', str, length);
		calculateSingleOperation('+', str, length);
		calculateSingleOperation('-', str, length);
	}

	void calculateSingleOperation(const char operationSymbol, char* str, int& length) {

		Operations op;

		for (int i = 0; i < length; i++) {
			if (operationSymbol == str[i]) {
				// see what the coefficient of the number to the right and the number to the left is
				// check if the operation can be made

				int checkLeft = checkForX(str, i, true);
				int checkRight = checkForX(str, i, false);

				// selects the number left to the found symbol
				char leftNum[100]; int leftNumIndex;
				//selectNumberToTheLeft(str, leftNum, i, leftNumIndex);

				// selects the number right to the found symbol
				char rightNum[100]; int rightNumIndex;
				//selectNumberToTheRight(str, rightNum, i, rightNumIndex);

				// calculates the result of the operation between the right and left numbers of the symbol
				double result;
				bool resultFound = false;
				switch (operationSymbol) {
				case '#': result = op.root(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum)); resultFound = true; break;
				case '^': result = op.power(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum)); resultFound = true; break;
				case '*': result = op.multiplication(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum)); resultFound = true; break;
				case '/': result = op.division(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum)); resultFound = true; break;
				case '+':
					if (i - 1 >= 0 && Helper::isThisCharPartOfNumber(str[i - 1])) {
						result = op.addition(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum));
						resultFound = true;
					}
					break;
				case '-':
					if (i - 1 >= 0 && Helper::isThisCharPartOfNumber(str[i - 1])) {
						result = op.subtraction(Helper::charArrayToDouble(leftNum), Helper::charArrayToDouble(rightNum));
						resultFound = true;
					}
					break;
				}

				if (!resultFound)
					continue;

				// replaces the numbers and symbol with the result
				calcProcessor.replace(str, leftNumIndex, rightNumIndex, result, calcProcessor.numberPrecision);
				i = 0;
				length = strlen(str);
			}
			calcProcessor.solveMultipleSignProblems(str);
		}
	}

	int checkForX(char* str, int pivot, bool checkToTheLeft) {
		int posOfX = -1;
		if (checkToTheLeft) {
			for (int i = pivot - 1; i >= 0; i--) {
				if (!Helper::isThisCharPartOfNumber(str[i])) {
					if (str[i] == 'x') {
						posOfX = i;
						break;
					}
				}
			}
		}
		else {
			for (int i = pivot + 1; i < strlen(str); i++) {
				if (str[i] == 'x') {
					posOfX = i;
				}
			}
		}

		if (posOfX != -1) {
			if (str[posOfX + 1] == '^')
				return 2;
			else
				return 1;
		}
		else
			return 0;
	}









	void moveFromRightToLeft(char* str) {
		/*
		int foundEqual = -1;
		
		for (int i = 0; i < strlen(str); i++) 
			if (str[i] == '=') 
				foundEqual = i;
		
		if (foundEqual == -1)
			return;
		
		for (int i = foundEqual; i < strlen(str); i++) {
			if (!calcProcessor.isThisCharPartOfNumber(str[i])) {
				if (str[i] != '-' || i - 1 >= 0 && calcProcessor.isThisCharPartOfNumber(str[i - 1])) {
					char selectedGroup[100]; int groupIndex;
					calcProcessor.selectNumberToTheRight(str, selectedGroup, i, groupIndex);
					cout << "|" << selectedGroup << endl;
					invertGroup(selectedGroup);
					calcProcessor.replace(str, i + 1, groupIndex,Helper::charArrayToDouble(selectedGroup));
					cout << "|" << selectedGroup << endl;
				}
			}
		}*/
	}

	void selectGroup(char* str, char* result, int pivot, int& selectIndex) {
		
	}

	void invertGroup(char* num) {
		int length = strlen(num);
		if (num[0] == '-') {
			for (int i = 0; i < length - 1; i++)
				num[i] = num[i + 1];
			num[length -1] = '\0';
		}
		else {
			for (int i = length; i > 0 ; i--)
				num[i] = num[i - 1];
			num[0] = '-';
			num[length+1] = '\0';
		}
	}


};