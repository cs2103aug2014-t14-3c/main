//@author A0116781A-unused
#include "stdafx.h"
#include "IReceiver.h"

vector<string> IReceiver::outputMessageStorage;

vector<string> IReceiver::initialise() {
	outputMessageStorage = Executor::initialise();

	return outputMessageStorage;
}

vector<string> IReceiver::receive(string userCommand) { 

	try{
		outputMessageStorage = Executor::execute(userCommand);
	}
	catch(exception& e){
			
		ofstream file;
		file.open("JustAddIt/Logs/error.log", ios::app);
		file << "exception occurred: \"" <<  e.what() << "\" \n command entered: \"" << userCommand << "\"\n" << endl;
		file.close();

		string errorMessage = "<span style=\"color:#CC0000;\">Woops! ";
		errorMessage += e.what();
		outputMessageStorage.push_back(errorMessage);
	}

	return outputMessageStorage;
}