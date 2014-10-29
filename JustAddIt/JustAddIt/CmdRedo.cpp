#include "stdafx.h"
#include "CmdRedo.h"


CmdRedo::CmdRedo(void)
{
}


CmdRedo::~CmdRedo(void)
{
}

vector<string> CmdRedo::execute() {
	ActionLog::redo();

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase->execute();

	return outputMessageStorage;
}
