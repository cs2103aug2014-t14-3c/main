#include "stdafx.h"
#include "CmdDeleteItem.h"

const string CmdDeleteItem::MESSAGE_DELETION_SUCCESSFUL = "Item(s) successfully deleted!";
const string CmdDeleteItem::LOG_ITEMS_DELETED = "INFO: Items deleted from ItemBank::bank";
const string CmdDeleteItem::LOG_BASE_SCREEN_STORED = "INFO: outputMessageStorage stores base screen";
const string CmdDeleteItem::LOG_SUCCESS_MESSAGE_STORED = "INfO: Success message is stored into outputMessageStorage";
const string CmdDeleteItem::LOG_COMMAND_STORED_IN_ACTION_LOG = "INFO: Command is stored into ActionLog";
const string CmdDeleteItem::ERROR_EMPTY_VECTOR = "Please choose one or more Items to delete!";
const string CmdDeleteItem::TEXT_FILE_NAME = "CmdDeleteItem_Log.txt";

CmdDeleteItem::CmdDeleteItem(vector<Item*> itemsToBeDeleted) {
	_itemsToBeDeleted = itemsToBeDeleted;

	if (_itemsToBeDeleted.size() == 0) {
		throw invalid_argument(ERROR_EMPTY_VECTOR);
	}
}

CmdDeleteItem::~CmdDeleteItem(void) {
}

//This function first deletes items based on their addresses in ItemBank::bank and then stores the base screen
//together with a success message into outputMessageStorage. The outputMessageStorage is then returned for 
//display.
vector<string> CmdDeleteItem::execute() {

	deleteItemsFromBank();

	outputMessageStorage.clear();
	outputMessageStorage = returnToBaseScreen();

	outputMessageStorage.push_back(MESSAGE_DELETION_SUCCESSFUL);
	writeToLog(LOG_SUCCESS_MESSAGE_STORED);

	storeCommandIntoActionLog();

	return outputMessageStorage;
}

//This function calls for Itembank to delete the items in the _itemsToBeDeleted vector
void CmdDeleteItem::deleteItemsFromBank(void) {
	ItemBank::deleteFromBank(_itemsToBeDeleted);

	writeToLog(LOG_ITEMS_DELETED);
}

//This function first retrieve the base screen information from OutputControl, contructs it and stores it
//inside screenToBeDisplayed. screenToBeDiplayed is then returned.
vector<string> CmdDeleteItem::returnToBaseScreen(void) {
	vector<string>screenToBeDisplayed;

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	screenToBeDisplayed = cmdBase->execute();

	writeToLog(LOG_BASE_SCREEN_STORED);

	return screenToBeDisplayed;
}

//This function updates the ActionLog which will be used during undo/redo functions
void CmdDeleteItem::storeCommandIntoActionLog(void) {
	ActionLog::addCommand(this);

	writeToLog(LOG_COMMAND_STORED_IN_ACTION_LOG);
}

void CmdDeleteItem::writeToLog (string logEntry) {
	ofstream mytextfile;
	mytextfile.open(TEXT_FILE_NAME, ios::app);

	mytextfile << logEntry << endl;

	mytextfile.close();
}