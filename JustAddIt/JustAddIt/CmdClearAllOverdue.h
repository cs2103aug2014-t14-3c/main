//@author A0128461H
#pragma once
#include "stdafx.h"
#include "Command.h"
#include "CmdGoToBaseScreen.h"
#include "ActionLog.h"

class CmdClearAllOverdue:
	public Command
{
private:
	void writeToLog (string logEntry);

public:
	static const string TEXT_FILE_NAME;
	static const string CLEARED_ALL_OVERDUE_DEADLINES_LOG;
	static const string ERROR_MESSAGE;
	static const string SUCCESS_MESSAGE;

	CmdClearAllOverdue(void);
	~CmdClearAllOverdue(void);

	vector<string> execute();
};

