#pragma once
#include "command.h"
#include "ActionLog.h"
#include "CmdGoToBaseScreen.h"

class CmdUndo :
	public Command
{
public:
	CmdUndo(void);
	~CmdUndo(void);

	vector<string> execute();
	void addToActionLog();
};

