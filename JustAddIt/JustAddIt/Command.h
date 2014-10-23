#pragma once

#include "stdafx.h"
#include "ItemBank.h"
#include "OutputControl.h"

using namespace std;

class Command
{
protected:
	enum CmdStatus {
		EXECUTE,
		UNDO,
		REDO
	};
	vector<string> outputMessageStorage;
	CmdStatus status;

public:
	Command(void);
	~Command(void);
	virtual vector<string> execute();
	virtual vector<string> undo();
	virtual vector<string> redo();

};