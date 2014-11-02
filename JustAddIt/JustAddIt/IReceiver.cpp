#include "stdafx.h"
#include "IReceiver.h"

vector<string> IReceiver::outputMessageStorage;

vector<string> IReceiver::initialise() {
	outputMessageStorage = Executor::initialise();

	return outputMessageStorage;
}

vector<string> IReceiver::receive(string userCommand) { 
	//Initialise itembank
	//Output home screen
	//Prompt for command

//	string userCommand = "";
//	vector<string>::iterator iter;

//	outputMessageStorage = Executor::initialise();

//	for (iter = outputMessageStorage.begin(); iter != outputMessageStorage.end(); iter++) {
//		cout << *iter << endl;
//	}

//	cout << "command: ";
//	getline(cin, userCommand);

//	while (userCommand != "exit") {
		try{ // TODO: Move this to GUI
			outputMessageStorage = Executor::execute(userCommand);

//			for (iter = outputMessageStorage.begin(); iter != outputMessageStorage.end(); iter++) {
//				cout << *iter << endl;
//				}
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

//		cout << "command: ";
//		getline(cin, userCommand); 
//	};
	return outputMessageStorage;
}