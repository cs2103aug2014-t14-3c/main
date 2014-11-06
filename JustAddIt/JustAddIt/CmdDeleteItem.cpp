//@author A0108397W
#include "stdafx.h"
#include "CmdDeleteItem.h"

const string CmdDeleteItem::MESSAGE_DELETION_SUCCESSFUL = "Item(s) successfully deleted!";
const string CmdDeleteItem::LOG_ITEMS_DELETED = "INFO: Items deleted from ItemBank::bank";
const string CmdDeleteItem::LOG_BASE_SCREEN_STORED = "INFO: outputMessageStorage stores base screen";
const string CmdDeleteItem::LOG_SUCCESS_MESSAGE_STORED = "INfO: Success message is stored into outputMessageStorage";
const string CmdDeleteItem::LOG_ACTION_LOG_UPDATED = "INFO: Command is stored into ActionLog";
const string CmdDeleteItem::ERROR_EMPTY_VECTOR = "Please choose one or more Items to delete!";
const string CmdDeleteItem::TEXT_FILE_NAME = "CmdDeleteItem_Log.txt";

CmdDeleteItem::CmdDeleteItem(vector<Item*> itemsToDelete) {
	_itemsToDelete = itemsToDelete;

	if (_itemsToDelete.size() == 0) {
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

	storeSuccessMessage();

	storeCommandIntoActionLog();

	return outputMessageStorage;
}

//This function calls for Itembank to delete the items in the _itemsToDelete vector
void CmdDeleteItem::deleteItemsFromBank(void) {
	ItemBank::deleteItems(_itemsToDelete);

	writeToLog(LOG_ITEMS_DELETED);
}

<<<<<<< HEAD
//This function first retrieve the base screen information from OutputControl, constructs it and stores it
//inside baseScreenToBeDisplayed. baseScreenToBeDiplayed is then returned.
vector<string> CmdDeleteItem::returnToBaseScreen(void) {
	vector<string>baseScreenToBeDisplayed;

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	baseScreenToBeDisplayed = cmdBase->execute();

	writeToLog(LOG_BASE_SCREEN_STORED);

	return baseScreenToBeDisplayed;
}

void CmdDeleteItem::storeSuccessMessage() {
	outputMessageStorage.push_back(MESSAGE_DELETION_SUCCESSFUL);

	writeToLog(LOG_SUCCESS_MESSAGE_STORED);
=======
//This function first retrieve the base screen information from OutputControl, contructs it and stores it
//inside screen. screenToBeDiplayed is then returned.
vector<string> CmdDeleteItem::returnToBaseScreen(void) {
	vector<string>screen;

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	screen = cmdBase->execute();

	writeToLog(LOG_BASE_SCREEN_STORED);

	return screen;
>>>>>>> 551ce82ec438c8da07f28ce4169c32055e33867b
}

//This function updates the ActionLog which will be used during undo/redo functions
void CmdDeleteItem::storeCommandIntoActionLog(void) {
	ActionLog::addCommand(this);

	writeToLog(LOG_ACTION_LOG_UPDATED);
}

void CmdDeleteItem::writeToLog (string logEntry) {
	ofstream mytextfile;
	mytextfile.open(TEXT_FILE_NAME, ios::app);

	mytextfile << logEntry << endl;

	mytextfile.close();
}