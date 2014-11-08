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
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase->execute();
	return outputMessageStorage;
}

void CmdUndo::addToActionLog() {
	//do nothing
}