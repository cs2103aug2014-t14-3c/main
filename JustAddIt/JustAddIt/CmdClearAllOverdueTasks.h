#pragma once
#include "Command.h"

class CmdClearAllOverdueTasks :
	public Command
{
public:
	CmdClearAllOverdueTasks(void);
	~CmdClearAllOverdueTasks(void);

	vector<string> execute();
};

