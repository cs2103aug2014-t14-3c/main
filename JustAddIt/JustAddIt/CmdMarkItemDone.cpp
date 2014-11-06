//@author A0108397W
#include "stdafx.h"
#include "CmdMarkItemDone.h"

const string CmdMarkItemDone::MESSAGE_MARK_SUCCESSFUL = "Item(s) successfully marked!";
const string CmdMarkItemDone::LOG_ITEMS_MARKED = "INFO: Items marked in ItemBank::bank";
const string CmdMarkItemDone::LOG_BASE_SCREEN_STORED = "INFO: outputMessageStorage stores base screen";
const string CmdMarkItemDone::LOG_SUCCESS_MESSAGE_STORED = "INfO: Success message is stored into outputMessageStorage";
const string CmdMarkItemDone::LOG_ACTION_LOG_UPDATED = "INFO: Command is stored into ActionLog";
const string CmdMarkItemDone::ERROR_EMPTY_VECTOR = "Please choose one or more Items to mark!";
const string CmdMarkItemDone::TEXT_FILE_NAME = "CmdMarkItemDone_Log.txt";

CmdMarkItemDone::CmdMarkItemDone(vector<Item*> itemsToBeMarked) {
	_itemsToBeMarked = itemsToBeMarked;

	if (_itemsToBeMarked.size() == 0) {
		throw invalid_argument(ERROR_EMPTY_VECTOR);
	}
}

CmdMarkItemDone::~CmdMarkItemDone(void) {
}

//This function first marks items based on their addresses in ItemBank::bank and then stores the base screen
//together with a success message into outputMessageStorage. The outputMessageStorage is then returned for 
//display.
vector<string> CmdMarkItemDone::execute() {

	toggleItemsDone();

	outputMessageStorage.clear();
	outputMessageStorage = returnToBaseScreen();

	storeSuccessMessage();

	storeCommandIntoActionLog();

	return outputMessageStorage;
}

//This function calls for Itembank to mark the items in the _itemsToBeMarked vector
void CmdMarkItemDone::toggleItemsDone(void) {
	ItemBank::toggleItemsDone(_itemsToBeMarked);

	writeToLog(LOG_ITEMS_MARKED);
}

//This function first retrieve the base screen information from OutputControl, contructs it and stores it
//inside screenToBeDisplayed. screenToBeDiplayed is then returned.
vector<string> CmdMarkItemDone::returnToBaseScreen(void) {
	vector<string>screenToBeDisplayed;

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	screenToBeDisplayed = cmdBase->execute();

	writeToLog(LOG_BASE_SCREEN_STORED);

	return screenToBeDisplayed;
}

void CmdMarkItemDone::storeSuccessMessage(void) {
	outputMessageStorage.push_back(MESSAGE_MARK_SUCCESSFUL);

	writeToLog(LOG_SUCCESS_MESSAGE_STORED);
}

//This function updates the ActionLog which will be used during undo/redo functions
void CmdMarkItemDone::storeCommandIntoActionLog(void) {
	ActionLog::addCommand(this);

	writeToLog(LOG_ACTION_LOG_UPDATED);
}

void CmdMarkItemDone::writeToLog (string logEntry) {
	ofstream mytextfile;
	mytextfile.open(TEXT_FILE_NAME, ios::app);

	mytextfile << logEntry << endl;

	mytextfile.close();
}