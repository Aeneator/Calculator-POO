#pragma once
#include <iostream>
using namespace std;

class Menu {
public:

	virtual void showHelp(string outputMethod) = 0;

protected:
	char* convertToLowercase(const char* input) {
		if (input == nullptr) 
			return nullptr;  

		int length = strlen(input);

		char* result = new char[length + 1];

		for (int i = 0; i < length; ++i) 
			result[i] = tolower(static_cast<unsigned char>(input[i]));
		
		result[length] = '\0';

		return result;
	}

	void consoleRed(HANDLE h) {
		SetConsoleTextAttribute(h, FOREGROUND_RED);
	}

	void consoleBlue(HANDLE h) {
		SetConsoleTextAttribute(h, FOREGROUND_BLUE);
	}

	void consoleGreen(HANDLE h) {
		SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	}

	void resetConsole(HANDLE h) {
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

};

class CalculatorMenu : public Menu {
public:
	bool checkForExitCode(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return strcmp(lowercaseStr, "exit") == 0;
	}

	bool checkForHelpCode(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return (strcmp(lowercaseStr, "help") == 0);
	}

	bool checkForClearScreen(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return (strcmp(lowercaseStr, "clear") == 0);
	}

	bool checkForShowVariables(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return(strcmp(lowercaseStr, "showvariables") == 0);
	}

	bool checkForRemoveVariables(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return(strcmp(lowercaseStr, "removevariables") == 0);
	}

	bool checkForSaveVariablesToFile(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return(strcmp(lowercaseStr, "savevariables") == 0);
	}

	bool checkForLoadVariablesFromFile(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return(strcmp(lowercaseStr, "loadvariables") == 0);
	}

	bool checkForSaveVariablesToFileCustomName(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		char result[20];
		string prefix = "savevariablesto";
		strncpy_s(result, lowercaseStr, prefix.length());
		result[prefix.length()] = '\0';
		return(strcmp(result, prefix.c_str()) == 0);
	}

	bool checkForLoadVariablesFromFileCustomName(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		char result[20];
		string prefix = "loadvariablesfrom";
		strncpy_s(result, lowercaseStr, prefix.length());
		result[prefix.length()] = '\0';
		return(strcmp(result, prefix.c_str()) == 0);
	}

	bool checkForLoadExpressionsFromFile(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		char result[20];
		string prefix = "loadfile";
		strncpy_s(result, lowercaseStr, prefix.length());
		result[prefix.length()] = '\0';
		return(strcmp(result, prefix.c_str()) == 0);
	}

	bool checkForHistory(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return(strcmp(lowercaseStr, "history") == 0);
	}

	bool checkForSaveHistory(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return(strcmp(lowercaseStr, "savehistory") == 0);
	}

	bool checkForOutPutMehtodConsole(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		return(strcmp(lowercaseStr, "outputconsole") == 0);
	}

	bool checkForOutPutMehtodFile(char* str) {
		char* lowercaseStr = convertToLowercase(str);
		char result[20];
		string prefix = "outputfile";
		strncpy_s(result, lowercaseStr, prefix.length());
		result[prefix.length()] = '\0';
		return(strcmp(result, prefix.c_str()) == 0);
	}
	void showHelp(string outputMethod) override {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		consoleRed(hConsole);
		cout << "Commands for INPUTTING expressions" << endl;
		resetConsole(hConsole);
		cout << "   Type "; consoleGreen(hConsole); cout << "\"load file file_name.txt\""; resetConsole(hConsole); cout << " to load expressions from text file" << endl;
		
		consoleRed(hConsole);
		cout << "\nCommands for OUTPUTTING results" << endl;
		resetConsole(hConsole);
		cout << "   Type "; consoleGreen(hConsole); cout << "\"output console\""; resetConsole(hConsole); cout << " to output calculator results to the console" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"output file\""; resetConsole(hConsole); cout << " to output results to default file" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"output file file_name.txt\""; resetConsole(hConsole); cout << " to output results to the file file_name.txt" << endl;
		cout << "   Current output method: " << outputMethod << endl;
		
		consoleRed(hConsole);
		cout <<"\nVariables" <<endl;
		resetConsole(hConsole);
		cout << "   After writing an expression and pressing ENTER,\n   the user cand type:"; consoleGreen(hConsole); cout << " \"save as var_name\""; resetConsole(hConsole); cout << " to save the last result as a variable" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"show variables\""; resetConsole(hConsole); cout << " to SEE all current variables" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"remove variables\""; resetConsole(hConsole); cout << " to REMOVE all current variables" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"save variables\""; resetConsole(hConsole); cout << " to SAVE the current variables to the default text file" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"save variables to file_name\""; resetConsole(hConsole); cout << " to SAVE the current variables to the file_name file" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"load variables\""; resetConsole(hConsole); cout << " to LOAD the variables from the default text file" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"load variables from file_name\""; resetConsole(hConsole); cout << " to LOAD the variables from to file_name text file" << endl;
		
		consoleRed(hConsole);
		cout << "\nOther" << endl;
		resetConsole(hConsole);
		cout << "   Type "; consoleGreen(hConsole); cout << "\"history\""; resetConsole(hConsole); cout << " to show calculator history" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"clear\""; resetConsole(hConsole); cout << " to clear the console" << endl;
		cout << "   Type "; consoleGreen(hConsole); cout << "\"save history\""; resetConsole(hConsole); cout << " to save the current history the history.txt file" << endl;
		cout << endl;
	}
};