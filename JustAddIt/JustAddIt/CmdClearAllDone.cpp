//@author A0128461H
#include "stdafx.h"
#include "CmdClearAllDone.h"

CmdClearAllDone::CmdClearAllDone(void) {
}

CmdClearAllDone::~CmdClearAllDone(void) {
}

vector<string> CmdClearAllDone::execute() {
	ItemBank::getInstance() -> deleteDoneItems();

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase -> execute();
	outputMessageStorage.push_back("All completed Item(s) successfully deleted!");

	ActionLog::addCommand(this);

	return outputMessageStorage;
}
