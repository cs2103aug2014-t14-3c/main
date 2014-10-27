#include "stdafx.h"
#include "CmdClearAllDone.h"


CmdClearAllDone::CmdClearAllDone(void) {
}

CmdClearAllDone::~CmdClearAllDone(void) {
}

vector<string> CmdClearAllDone::execute() {
	ItemBank::deleteAllDoneItemsFromBank();


	//returns to base screen
	Command* cmdHome = new CmdHome;
	outputMessageStorage.clear();
	outputMessageStorage = cmdHome->execute();

	outputMessageStorage.push_back("All completed Item(s) successfully deleted!");

	return outputMessageStorage;
}
