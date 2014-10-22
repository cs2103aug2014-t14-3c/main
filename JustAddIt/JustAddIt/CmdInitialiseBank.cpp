#include "stdafx.h"
#include "CmdInitialiseBank.h"
#include "CmdHome.h"

CmdInitialiseBank::CmdInitialiseBank(void)
{
}

CmdInitialiseBank::~CmdInitialiseBank(void)
{
}

vector<string> CmdInitialiseBank::execute() {
	ItemBank::initialiseBank();

	Command* cmdHome = new CmdHome;
	outputMessageStorage.clear();
	outputMessageStorage = cmdHome->execute();

	return outputMessageStorage;
}