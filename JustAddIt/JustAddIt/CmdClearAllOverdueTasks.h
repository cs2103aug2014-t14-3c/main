#pragma once
#include "Command.h"
#include "ActionLog.h"

class CmdClearAllOverdueTasks :
	public Command
{
public:
	CmdClearAllOverdueTasks(void);
	~CmdClearAllOverdueTasks(void);

	vector<string> execute();
};

