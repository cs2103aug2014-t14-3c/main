//@author A0108397W
#include "stdafx.h"
#include "CmdShowOverdueDeadlines.h"

const string CmdShowOverdueDeadlines::LOG_OVERDUE_SCREEN_STORED = "INFO: Overdue screen has been constructed and stored in a string vector";
const string CmdShowOverdueDeadlines::LOG_OUTPUTCONTROL_UPDATED = "INFO: OutputControl is updated with the current command";
const string CmdShowOverdueDeadlines::LOG_OVERDUE_DEADLINES_RETRIEVED = "INFO: All overdue deadlines have been retrieved from Bank";
const string CmdShowOverdueDeadlines::TEXT_FILE_NAME = "JustAddIt/Logs/CmdShowOverdueDeadlines_Log.txt";

CmdShowOverdueDeadlines::CmdShowOverdueDeadlines(void) {
}

CmdShowOverdueDeadlines::~CmdShowOverdueDeadlines(void) {
}

//This function retrieves all overdue deadlines from ItemBank, constructs the overdue screen with the deadlines and returns it
vector<string> CmdShowOverdueDeadlines::execute() {
	vector<Item*> overdueDeadlines;

	overdueDeadlines = getOverdueDeadlinesFromBank();

	outputMessageStorage.clear();
	outputMessageStorage = storeOverdueScreenForDisplay(overdueDeadlines);

	updateOutputControl(overdueDeadlines);

	return outputMessageStorage;
}

vector<Item*> CmdShowOverdueDeadlines::getOverdueDeadlinesFromBank() {
	vector<Item*> overdueDeadlines;
	ItemBank* itemBank = ItemBank::getInstance();

	overdueDeadlines = itemBank->getOverdueDeadlines();

	writeToLog(LOG_OVERDUE_DEADLINES_RETRIEVED);

	return overdueDeadlines;
}

vector<string> CmdShowOverdueDeadlines::storeOverdueScreenForDisplay(vector<Item*> overdueDeadlines) {
	vector<string> overdueScreen;

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	overdueScreen = displayScreenConstructor->clearScreen();
	overdueScreen = displayScreenConstructor->constructOverdueScreen(overdueDeadlines);

	writeToLog(LOG_OVERDUE_SCREEN_STORED);

	return overdueScreen;
}

void CmdShowOverdueDeadlines::updateOutputControl(vector<Item*> overdueDeadlines) {
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::OVERDUE_TASKS_SCREEN);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::OVERDUE_TASKS_SCREEN);
	OutputControl::setCurrentDisplayedItemList(overdueDeadlines);

	writeToLog(LOG_OUTPUTCONTROL_UPDATED);
}

void CmdShowOverdueDeadlines::writeToLog (string logEntry) {
	ofstream mytextfile;
	mytextfile.open(TEXT_FILE_NAME, ios::app);

	mytextfile << logEntry << endl;

	mytextfile.close();
}