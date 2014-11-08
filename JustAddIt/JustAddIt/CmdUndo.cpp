//@author A0116781A
#include "stdafx.h"
#include "CmdUndo.h"


CmdUndo::CmdUndo(void)
{
}


CmdUndo::~CmdUndo(void)
{
}


vector<string> CmdUndo::execute() {

	ActionLog::undo();

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());

	return cmdBase->execute();
}

void CmdUndo::addToActionLog() {
	//do nothing
}