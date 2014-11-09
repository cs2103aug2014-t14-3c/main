//@author A0128461H
#include "stdafx.h"
#include "CmdClearAllDone.h"

const string CmdClearAllDone::TEXT_FILE_NAME = "../JustAddIt/JustAddIt/JustAddIt/Logs/CmdClearItem_Log.txt";
const string CmdClearAllDone::CLEARED_ALL_DONE_ITEMS_LOG = "All the done items are cleared.";
const string CmdClearAllDone::ERROR_MESSAGE = "No more done items to be cleared!";
const string CmdClearAllDone::SUCCESS_MESSAGE = "All completed Item(s) successfully deleted!";

CmdClearAllDone::CmdClearAllDone(void) {
}

CmdClearAllDone::~CmdClearAllDone(void) {
}

void CmdClearAllDone::writeToLog(string logEntry) {
	ofstream mytextfile;
	mytextfile.open(TEXT_FILE_NAME, ios::app);
	mytextfile << logEntry << endl;
	mytextfile.close();
}

vector<string> CmdClearAllDone::execute() {
	ItemBank* itemPointer = ItemBank::getInstance();
	if (itemPointer -> getNumberOfMarkedItems() == 0) {
		throw invalid_argument(ERROR_MESSAGE);
		writeToLog(ERROR_MESSAGE);
	}
	else {
		ItemBank::getInstance() -> deleteDoneItems();
		writeToLog(CLEARED_ALL_DONE_ITEMS_LOG);
	}

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase -> execute();
	outputMessageStorage.push_back(SUCCESS_MESSAGE);

	ActionLog::addCommand(this);

	return outputMessageStorage;
}

