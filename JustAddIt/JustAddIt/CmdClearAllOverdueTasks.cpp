#include "stdafx.h"
#include "CmdClearAllOverdueTasks.h"

CmdClearAllOverdueTasks::CmdClearAllOverdueTasks(void)
{
}


CmdClearAllOverdueTasks::~CmdClearAllOverdueTasks(void)
{
}

vector<string> CmdClearAllOverdueTasks::execute() {

	ActionLog::addCommand(this);

	return outputMessageStorage;
}