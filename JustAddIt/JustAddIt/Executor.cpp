//@author A0128461H
#include "stdafx.h"
#include "Executor.h"

vector<string> Executor::outputMessageStorage;

vector<string> Executor::execute(string userCommand) {
	Parser parser;
	Command* command;

	//DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	//outputMessageStorage.clear();
	//outputMessageStorage = displayScreenConstructor->clearScreen();

	try {
		command = parser.stringToCommand(userCommand);
		outputMessageStorage = command->execute();
	} catch (exception& e) {
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

vector<string> Executor::initialise() {
	try {
		Command* command = new CmdInitialiseBank();
		outputMessageStorage = command->execute();
	} catch (exception& e) {
		ofstream file;
		file.open("JustAddIt/Logs/error.log", ios::app);
		file << "exception occurred when initialising bank: \"" <<  e.what() << "\"\n" << endl;
		file.close();

		string errorMessage = "<span style=\"color:#CC0000;\">Woops! ";
		errorMessage += e.what();
		outputMessageStorage.push_back(errorMessage);
	}
	
	return outputMessageStorage;
}