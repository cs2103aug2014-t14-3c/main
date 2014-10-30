#include "stdafx.h"
#include "CmdClearAllOverdue.h"


CmdClearAllOverdue::CmdClearAllOverdue(void)
{
}


CmdClearAllOverdue::~CmdClearAllOverdue(void)
{
}

vector<string> CmdClearAllOverdue::execute() {
	ItemBank::deleteAllOverdueDeadlinesFromBank();


	//returns to base screen
	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase->execute();

	outputMessageStorage.push_back("All overdue Deadline(s) successfully deleted!");

	return outputMessageStorage;
}