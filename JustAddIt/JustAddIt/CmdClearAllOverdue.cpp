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
	Command* cmdHome = new CmdHome;
	outputMessageStorage.clear();
	outputMessageStorage = cmdHome->execute();

	outputMessageStorage.push_back("All overdue Deadline(s) successfully deleted!");

	return outputMessageStorage;
}