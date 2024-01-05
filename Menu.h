#pragma once
#include <iostream>
using namespace std;

class Menu {
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

	void resetConsole(HANDLE h) {
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

};

class CalculatorMenu : public Menu {
public:
	void showHelp(string outputMethod) override {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		consoleRed(hConsole);
		cout << "Commands for INPUTTING expressions" << endl;
		resetConsole(hConsole);
		cout << "   Type \"load file file_name.txt\" to load expressions from text file" << endl;
		
		consoleRed(hConsole);
		cout << "\nCommands for OUTPUTTING expression results" << endl;
		resetConsole(hConsole);
		cout << "   Type \"output console\" to output calculator results to the console" << endl;
		cout << "   Type \"output file\" to output results to default file" << endl;
		cout << "   Type \"output file file_name.txt\" to output results to the file file_name.txt" << endl;
		cout << "   Current output method: " << outputMethod << endl;
		
		consoleRed(hConsole);
		cout <<"\nVariables" <<endl;
		resetConsole(hConsole);
		cout << "   After writing an expression and pressing ENTER,\n   the user cand type: \"save as var_name\" to save the last result as a variable" << endl;
		cout << "   Type \"show variables\" to SEE all current variables" << endl;
		cout << "   Type \"remove variables\" to REMOVE all current variables" << endl;
		cout << "   Type \"save variables\" to SAVE the current variables to the default text file" << endl;
		cout << "   Type \"save variables to file_name\" to SAVE the current variables to the file_name file" << endl;
		cout << "   Type \"load variables\" to LOAD the variables from the default text file" << endl;
		cout << "   Type \"load variables from file_name\" to LOAD the variables from to file_name text file" << endl;
		
		consoleRed(hConsole);
		cout << "\nOther" << endl;
		resetConsole(hConsole);
		cout << "   Type \"history\" to show calculator history" << endl;
		cout << "   Type \"clear\" to clear the console" << endl;
		cout << endl;
	}
};