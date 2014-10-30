#include "stdafx.h"
#include "UI.h"

void UI::main() { 
	//Initialise itembank
	//Output home screen
	//Prompt for command

	string userCommand = "";
	vector<string> outputMessageStorage;
	vector<string>::iterator iter;
	Executor* executor = new Executor();

	outputMessageStorage = executor->initialise();

	for (iter = outputMessageStorage.begin(); iter != outputMessageStorage.end(); iter++) {
		cout << *iter << endl;
	}

	cout << "command: ";
	getline(cin, userCommand);

	while (userCommand != "exit") {
		try{
			outputMessageStorage = executor->execute(userCommand);

			for (iter = outputMessageStorage.begin(); iter != outputMessageStorage.end(); iter++) {
				cout << *iter << endl;
				}
			//for export, keep previous oms info
			//outputMessageStorage.clear(); 
			}
		catch(exception& e){
			cerr << "error: " << e.what() << endl;
			ofstream file;
			file.open("error.log");
			file << "exception occurred: " << userCommand << endl;
			file.close();
		}
		cout << "command: ";
		getline(cin, userCommand); 
	};
}