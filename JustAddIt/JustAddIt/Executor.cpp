//@author A0128461H
#include "stdafx.h"
#include "Executor.h"

vector<string> Executor::outputMessageStorage;

const string Executor::LOG_FILE_NAME = "JustAddIt/Logs/error.log";
const string Executor::LOG_EXECUTOR_EXECUTING_EXCEPTIONS_PART_1 = "exception occurred: \"";
const string Executor::LOG_EXECUTOR_EXECUTING_EXCEPTIONS_PART_2 = "\" \n command entered: \"";
const string Executor::LOG_EXECUTOR_INITIALISING_EXCEPTIONS = "exception occurred when initialising bank: \"";
const string Executor::NEWLINE_CHARACTERS = "\"\n";
const string Executor::ERROR_MESSAGE = "<span style=\"color:#CC0000;\">Woops! ";

vector<string> Executor::execute(string userCommand) {
	Parser parser;
	Command* command;

	try {
		command = parser.stringToCommand(userCommand);
		outputMessageStorage = command -> execute();
	} catch (exception& e) {
		ofstream file;
		file.open(LOG_FILE_NAME, ios::app);
		file << LOG_EXECUTOR_EXECUTING_EXCEPTIONS_PART_1 <<  e.what() << LOG_EXECUTOR_EXECUTING_EXCEPTIONS_PART_2 << userCommand << NEWLINE_CHARACTERS << endl;
		file.close();

		string errorMessage = ERROR_MESSAGE;
		errorMessage += e.what();
		outputMessageStorage.push_back(errorMessage);
	}

	return outputMessageStorage;
}

vector<string> Executor::initialise() {
	try {
		Command* command = new CmdInitialiseBank();
		outputMessageStorage = command -> execute();
	} catch (exception& e) {
		ofstream file;
		file.open(LOG_FILE_NAME, ios::app);
		file << LOG_EXECUTOR_INITIALISING_EXCEPTIONS <<  e.what() << NEWLINE_CHARACTERS << endl;
		file.close();

		string errorMessage = ERROR_MESSAGE;
		errorMessage += e.what();
		outputMessageStorage.push_back(errorMessage);
	}
	
	return outputMessageStorage;
}