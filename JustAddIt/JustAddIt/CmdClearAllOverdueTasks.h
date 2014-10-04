#pragma once
#include "Command.h"

class CmdClearAllOverdueTasks :
	public Command
{
public:
	CmdClearAllOverdueTasks(void);
	~CmdClearAllOverdueTasks(void);

	void execute();
};

