#pragma once
#include "stdafx.h"
#include "Executor.h"

class IReceiver
{
private:
	static vector<string> outputMessageStorage;

public:
	static vector<string> initialise();
	static vector<string> receive(string userCommand);
};

