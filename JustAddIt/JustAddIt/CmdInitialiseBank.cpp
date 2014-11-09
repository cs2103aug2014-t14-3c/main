#include "stdafx.h"
#include "CmdInitialiseBank.h"

CmdInitialiseBank::CmdInitialiseBank(void)
{
}

CmdInitialiseBank::~CmdInitialiseBank(void)
{
}

vector<string> CmdInitialiseBank::execute() {
	ItemBank::getInstance()->initialiseBank();
	
	Command* cmdHome = new CmdHome;
	outputMessageStorage.clear();
	outputMessageStorage = cmdHome->execute();

	return outputMessageStorage;
}