#include "stdafx.h"
#include "Executor.h"

vector<string> Executor::outputMessageStorage;

vector<string> Executor::execute(string userCommand) {
	Parser parser;
	Command* command;

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();

	try{
		command = parser.stringToCommand(userCommand);
		outputMessageStorage = command->execute();
		ActionLog::addCommand(*command);
	}
	
	catch(exception& e){
		cerr << "error: " << e.what() << endl;
		ofstream file;
		file.open("error.log");
		file << "exception occurred: " << userCommand << endl;
		file.close();
	}


	return outputMessageStorage;
}

vector<string> Executor::initialise() {
	Command* command = new CmdInitialiseBank();
	outputMessageStorage.clear();
	outputMessageStorage = command->execute();
	
	return outputMessageStorage;
}