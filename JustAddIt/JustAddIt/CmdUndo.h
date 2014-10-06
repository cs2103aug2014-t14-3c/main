#pragma once
#include "command.h"
#include "ActionLog.h"

class CmdUndo :
	public Command
{
public:
	CmdUndo(void);
	~CmdUndo(void);

	vector<string> execute();
	void addToActionLog();
};

