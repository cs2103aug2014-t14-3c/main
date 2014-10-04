#include "stdafx.h"
#include "Executor.h"

Executor::Executor(void)
{
}


Executor::~Executor(void)
{
}

vector<string> Executor::execute(string userCommand) {
	Parser parser;

	outputMessageStorage.clear();
	outputMessageStorage = parser.stringToCommand(userCommand)->execute();
	return outputMessageStorage;
}