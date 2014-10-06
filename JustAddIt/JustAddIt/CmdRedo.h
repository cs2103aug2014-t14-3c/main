#pragma once
#include "command.h"
#include "ActionLog.h"

class CmdRedo :
	public Command
{
public:
	CmdRedo(void);
	~CmdRedo(void);

	vector<string> execute();
	void addToActionLog();
};

