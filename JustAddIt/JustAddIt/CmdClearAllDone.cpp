#include "stdafx.h"
#include "CmdClearAllDone.h"


CmdClearAllDone::CmdClearAllDone(void) {
}

CmdClearAllDone::~CmdClearAllDone(void) {
}

vector<string> CmdClearAllDone::execute() {
	ItemBank::deleteAllDoneItemsFromBank();


	//returns to base screen
	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase->execute();

	outputMessageStorage.push_back("All completed Item(s) successfully deleted!");

	return outputMessageStorage;
}
