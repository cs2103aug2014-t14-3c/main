//@author A0128461H
#pragma once
#include "Command.h"
#include "Parser.h"
#include "CmdInitialiseBank.h"
#include "DisplayScreenConstructor.h"
#include "ActionLog.h"

using namespace std;

class Executor
{
private:
	static vector<string> outputMessageStorage;

public:
	static const string LOG_FILE_NAME;
	static const string LOG_EXECUTOR_EXECUTING_EXCEPTIONS_PART_1;
	static const string LOG_EXECUTOR_EXECUTING_EXCEPTIONS_PART_2;
	static const string LOG_EXECUTOR_INITIALISING_EXCEPTIONS;
	static const string NEWLINE_CHARACTERS;
	static const string ERROR_MESSAGE;

	static vector<string> execute(string userCommand);
	static vector<string> initialise();
};