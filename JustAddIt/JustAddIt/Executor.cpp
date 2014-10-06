#include "stdafx.h"
#include "Executor.h"

vector<string> Executor::outputMessageStorage;

Executor::Executor(void)
{
}


Executor::~Executor(void)
{
}

vector<string> Executor::execute(string userCommand) {
	Parser parser;
	Command command;

	outputMessageStorage.clear();

	command = *(parser.stringToCommand(userCommand));
	outputMessageStorage = command.execute();
	ActionLog::addCommand(command);

	return outputMessageStorage;
}