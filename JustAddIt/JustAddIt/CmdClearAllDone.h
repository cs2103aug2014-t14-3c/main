//@author A0128461H
#pragma once
#include "stdafx.h"
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"
#include "CmdGoToBaseScreen.h"
#include "ActionLog.h"

class CmdClearAllDone:
	public Command
{
private:
	void writeToLog (string logEntry);

public:
	static const string TEXT_FILE_NAME;
	static const string CLEARED_ALL_DONE_ITEMS_LOG;
	static const string ERROR_MESSAGE;
	static const string SUCCESS_MESSAGE;

	CmdClearAllDone(void);
	~CmdClearAllDone(void);

	vector<string> CmdClearAllDone::execute();
};