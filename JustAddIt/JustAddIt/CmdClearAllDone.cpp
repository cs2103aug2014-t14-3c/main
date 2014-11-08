//@author A0128461H
#include "stdafx.h"
#include "CmdClearAllDone.h"

CmdClearAllDone::CmdClearAllDone(void) {
}

CmdClearAllDone::~CmdClearAllDone(void) {
}

vector<string> CmdClearAllDone::execute() {
	ItemBank* itemPointer = ItemBank::getInstance();
	if (itemPointer -> getNumberOfMarkedItems() == 0) {
		throw invalid_argument("No more done items to be cleared!");
	}
	else {
		ItemBank::getInstance() -> deleteDoneItems();
	}

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase -> execute();
	outputMessageStorage.push_back("All completed Item(s) successfully deleted!");

	ActionLog::addCommand(this);

	return outputMessageStorage;
}
