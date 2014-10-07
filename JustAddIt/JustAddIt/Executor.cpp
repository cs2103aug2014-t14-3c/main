#include "stdafx.h"
#include "Executor.h"

vector<string> Executor::outputMessageStorage;

vector<string> Executor::execute(string userCommand) {
	Parser parser;
	Command* command;

	clearScreen();

	command = parser.stringToCommand(userCommand);
	outputMessageStorage = command->execute();
	ActionLog::addCommand(*command);

	return outputMessageStorage;
}

vector<string> Executor::initialise() {
	Command* command = new CmdInitialiseBank();
	outputMessageStorage = command->execute();
	
	return outputMessageStorage;
}

void Executor::clearScreen() {
	outputMessageStorage.clear();
	
	cout << string(50, '\n');

	return;
}