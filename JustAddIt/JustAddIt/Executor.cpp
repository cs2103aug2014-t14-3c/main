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

	command = parser.stringToCommand(userCommand);
	outputMessageStorage = command->execute();
//	ActionLog::addCommand(command);

	return outputMessageStorage;
}

vector<string> Executor::initialise() {
	Command* command = new CmdInitialiseBank();
	outputMessageStorage.clear();
	outputMessageStorage = command->execute();
	
	return outputMessageStorage;
}