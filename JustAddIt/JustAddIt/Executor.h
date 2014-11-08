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
	static vector<string> execute(string userCommand);
	static vector<string> initialise();
};