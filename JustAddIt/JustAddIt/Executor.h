#pragma once
#include "Parser.h"
#include "Command.h"
#include "ActionLog.h"

using namespace std;

class Executor
{
private:
	static vector<string> outputMessageStorage;

public:
	Executor(void);
	~Executor(void);
	vector<string> execute(string userCommand);
};