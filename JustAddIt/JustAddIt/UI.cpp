#include "stdafx.h"
#include "UI.h"

void UI::main() { 
	//Initialise itembank
	//Output home screen
	//Prompt for command

	string userCommand = "";
	vector<string> outputMessageStorage;
	vector<string>::iterator iter;
	Executor executor;

	outputMessageStorage = executor.initialise();

	for (iter = outputMessageStorage.begin(); iter != outputMessageStorage.end(); iter++) {
		cout << *iter << endl;
	}

	cout << "command: ";
	getline(cin, userCommand);

	while (userCommand != "exit") {
	outputMessageStorage = executor.execute(userCommand);

	for (iter = outputMessageStorage.begin(); iter != outputMessageStorage.end(); iter++) {
		cout << *iter << endl;
	}

	outputMessageStorage.clear();
	cout << "command: ";
	getline(cin, userCommand); 
	};
}