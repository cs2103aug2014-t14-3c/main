#pragma once

#include "stdafx.h"
//@author A0110770U
#include "ItemBank.h"
#include "OutputControl.h"

using namespace std;

class Command
{
protected:
	vector<string> outputMessageStorage;

public:
	Command(void);
	~Command(void);
	virtual vector<string> execute();
};