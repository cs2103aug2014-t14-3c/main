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
	return outputMessageStorage;
}

void CmdUndo::addToActionLog() {
	//do nothing
}