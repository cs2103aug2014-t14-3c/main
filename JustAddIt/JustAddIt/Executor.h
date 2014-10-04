#pragma once
#include "Parser.h"
#include "Command.h"

using namespace std;

class Executor
{
private:
	vector<string> outputMessageStorage;

public:
	Executor(void);
	~Executor(void);
	vector<string> execute(string userCommand);

};