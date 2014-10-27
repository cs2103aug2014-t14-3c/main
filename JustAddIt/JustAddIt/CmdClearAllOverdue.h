#pragma once
#include "stdafx.h"
#include "Command.h"
#include "CmdHome.h"

class CmdClearAllOverdue :
	public Command
{
public:
	CmdClearAllOverdue(void);
	~CmdClearAllOverdue(void);
	vector<string> execute();
};

