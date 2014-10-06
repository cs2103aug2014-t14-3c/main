#include "stdafx.h"
#include "CmdInitialiseBank.h"

const string CmdInitialiseBank::MESSAGE_WELCOME = "____________________________\n|                          |\n|   Welcome to JustAddIt   |\n|__________________________|\n";
const string CmdInitialiseBank::MESSAGE_WELCOME_PAGE_INFO = "What do you want to do?\n\nUniversal commands: /add {task detail}\n /undo /return /search\n";


CmdInitialiseBank::CmdInitialiseBank(void)
{
}


CmdInitialiseBank::~CmdInitialiseBank(void)
{
}

vector<string> CmdInitialiseBank::execute() {
	ItemBank::initialiseBank();
	
	outputMessageStorage.push_back(MESSAGE_WELCOME);
	
	// produce calendar view
	// welcome pg qns
	// pg cmds available

	return outputMessageStorage;
}