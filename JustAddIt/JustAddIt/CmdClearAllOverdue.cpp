//@author A0128461H
#include "stdafx.h"
#include "CmdClearAllOverdue.h"

const string CmdClearAllOverdue::ERROR_MESSAGE = "No more overdue deadlines to be cleared!";
const string CmdClearAllOverdue::TEXT_FILE_NAME = "JustAddIt/Logs/CmdEditItem_Log.txt";
const string CmdClearAllOverdue::CLEARED_ALL_OVERDUE_DEADLINES_LOG = "All the overdue deadlines are cleared.";

CmdClearAllOverdue::CmdClearAllOverdue(void) {
}

CmdClearAllOverdue::~CmdClearAllOverdue(void) {
}

void CmdClearAllOverdue::writeToLog(string logEntry) {
	ofstream mytextfile;
	mytextfile.open(TEXT_FILE_NAME, ios::app);
	mytextfile << logEntry << endl;
	mytextfile.close();
}

vector<string> CmdClearAllOverdue::execute() {
	ItemBank* itemPointer = ItemBank::getInstance();
	if (itemPointer -> getOverdueDeadlines().size() == 0) {
		throw invalid_argument(ERROR_MESSAGE);
		writeToLog(ERROR_MESSAGE);
	}
	else {
		ItemBank::getInstance() -> deleteOverdueDeadlines();
		writeToLog(CLEARED_ALL_OVERDUE_DEADLINES_LOG);
	}

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase -> execute();
	outputMessageStorage.push_back("All overdue Deadline(s) successfully deleted!");

	ActionLog::addCommand(this);

	return outputMessageStorage;
}