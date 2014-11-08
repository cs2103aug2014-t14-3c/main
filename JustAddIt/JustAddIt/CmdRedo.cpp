//@author A0116781A
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

	return cmdBase->execute();
}

void CmdRedo::addToActionLog() {
	//do nothing
}
