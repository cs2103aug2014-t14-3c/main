#pragma once
#include "command.h"
#include "ItemBank.h"
#include "ActionLog.h"

class CmdGoToListView :
	public Command
{
private:
	int _numWeeks;

public:
	CmdGoToListView(int numWeeks);
	CmdGoToListView();
	~CmdGoToListView(void);

	vector<string> execute();
};

