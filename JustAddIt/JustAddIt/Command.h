#pragma once

#include "ItemBank.h"

using namespace std;

class Command
{
protected:
	vector<string> outputMessageStorage;

public:
	Command(void);
	~Command(void);
	vector<string> execute();
};