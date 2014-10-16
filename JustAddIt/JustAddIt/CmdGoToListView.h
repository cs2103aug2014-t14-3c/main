#pragma once
#include "command.h"
#include "ItemBank.h"

class CmdGoToListView :
	public Command
{
private:
	int _numWeeks;

public:
	CmdGoToListView(int numWeeks);
	~CmdGoToListView(void);

	vector<string> execute();
};

