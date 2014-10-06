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
	return outputMessageStorage;
}
