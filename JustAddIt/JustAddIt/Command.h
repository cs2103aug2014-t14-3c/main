//@author A0110770U
#pragma once
#include "stdafx.h"
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