#pragma once
#include "command.h"
#include "ActionLog.h"
#include "CmdGoToBaseScreen.h"

class CmdRedo :
	public Command
{
public:
	CmdRedo(void);
	~CmdRedo(void);

	vector<string> execute();
};

