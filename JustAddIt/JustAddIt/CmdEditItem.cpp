//@author A0108397W
#include "stdafx.h"
#include "CmdEditItem.h"

const string CmdEditItem::MESSAGE_EDIT_SUCCESSFUL = "Item is successfully edited!";
const string CmdEditItem::ERROR_PROGRAM_MALFUNCTION = "An error has occurred!";
const string CmdEditItem::ERROR_INVALID_FIELD_NUMBER = "Invalid field number! Please enter a valid field number 1 - 6.";
const string CmdEditItem::ERROR_EMPTY_FIELD = "Empty input! Please enter a valid input.";
const string CmdEditItem::LOG_OUTPUTCONTROL_UPDATED = "INFO: Output control is updated";
const string CmdEditItem::LOG_ACTION_LOG_UPDATED = "INFO: Command is stored into ActionLog";
const string CmdEditItem::LOG_SUCCESS_MESSAGE_STORED = "INFO: Success message is stored into outputMessageStorage";
const string CmdEditItem::LOG_EDIT_SCREEN_STORED = "INFO: Edit screen is stored and returned to be displayed";
const string CmdEditItem::LOG_EDIT_FIELD_DETERMINED = "INFO: Field to be edited is determined";
const string CmdEditItem::LOG_ITEM_EDITED = "INFO: Item field is edited";
const string CmdEditItem::TEXT_FILE_NAME = "JustAddIt/Logs/CmdEditItem_Log.txt";
enum FIELD_TO_BE_EDITED {EDIT_TITLE, EDIT_DESCRIPTION, EDIT_START_TIME, EDIT_END_TIME, EDIT_PRIORITY, EDIT_CATEGORY, INVALID};

//This constructor is used when editing items fields that contain strings variables (i.e. title, description, priority,
//category)
CmdEditItem::CmdEditItem(vector<Item*>::iterator bankPtr, int fieldNum, string newFieldInfo) {
	assert(*bankPtr != nullptr);

	if (fieldNum != 1 && fieldNum != 2 && fieldNum != 3 && fieldNum != 4 && fieldNum != 5 && fieldNum != 6) {
		throw invalid_argument(ERROR_INVALID_FIELD_NUMBER);
	}

	if (newFieldInfo == "") {
		newFieldInfo = "-"; //storing "" into DataStorage will cause the program to crash during reinitialisation
	}

	_itemAddr = *bankPtr;
	_editFieldNumber = fieldNum;
	_newFieldInfo = newFieldInfo;
	_isEditField = true;
}

//This constructor is used when editing start and end date time
CmdEditItem::CmdEditItem(vector<Item*>::iterator bankPtr, int fieldNum, tm newTimeInfo) {
	assert(*bankPtr != nullptr);

	if (fieldNum != 1 && fieldNum != 2 && fieldNum != 3 && fieldNum != 4 && fieldNum != 5 && fieldNum != 6) {
		throw invalid_argument(ERROR_INVALID_FIELD_NUMBER);
	}

	_itemAddr = *bankPtr;
	_editFieldNumber = fieldNum;
	_newTimeInfo = newTimeInfo;
	_isEditField = true;
}

//This constructor is used when selecting an item to be edited from a list
CmdEditItem::CmdEditItem(vector<Item*>::iterator bankPtr) {
	assert(*bankPtr != nullptr);

	_itemAddr = *bankPtr;
	_isEditField = false;
}

CmdEditItem::~CmdEditItem(void) {
}

//This function is used to edit an item using its address and return a edit screen which will be displayed to the user
vector<string> CmdEditItem::execute() {
	editItem();

	outputMessageStorage.clear();
	outputMessageStorage = storeEditScreenForDisplay();

	storeSuccessMessage();

	updateOutputControl();

	return outputMessageStorage;
}

//This function invokes the corresponding edit functions in the ItemBank class based on the user's input
void CmdEditItem::editItem() {
	ItemBank* itemBank = ItemBank::getInstance();

	if(_isEditField){
		FIELD_TO_BE_EDITED editField = determineEditField();

		switch (editField) {
		case EDIT_TITLE: {
			itemBank->editItemTitle(_itemAddr, _newFieldInfo);
			break;
						 }
		case EDIT_DESCRIPTION: {
			itemBank->editItemDescription(_itemAddr, _newFieldInfo);
			break;
							   }
		case EDIT_START_TIME: {
			itemBank->editItemStartDateTime(_itemAddr, _newTimeInfo);
			break;
							  }
		case EDIT_END_TIME: {
			itemBank->editItemEndDateTime(_itemAddr, _newTimeInfo);
			break;
							}
		case EDIT_PRIORITY: {
			itemBank->editItemPriority(_itemAddr, _newFieldInfo);
			break;
							}
		case EDIT_CATEGORY: {
			itemBank->editItemCategory(_itemAddr, _newFieldInfo);
			break;
							}
		case INVALID: {
			throw invalid_argument(ERROR_INVALID_FIELD_NUMBER);
			break;
					  }
		default: {
			throw invalid_argument(ERROR_PROGRAM_MALFUNCTION);
			break;
				 }
		}

		storeCommandIntoActionLog();
	}

	writeToLog(LOG_ITEM_EDITED);
}

FIELD_TO_BE_EDITED CmdEditItem::determineEditField() {
	if (_editFieldNumber == 1) {
		return EDIT_TITLE;
	}
	else if (_editFieldNumber == 2) {
		return EDIT_DESCRIPTION;
	}
	else if (_editFieldNumber == 3) {
		return EDIT_START_TIME;
	}
	else if (_editFieldNumber == 4) {
		return EDIT_END_TIME;
	}
	else if (_editFieldNumber == 5) {
		return EDIT_PRIORITY;
	}
	else if (_editFieldNumber == 6) {
		return EDIT_CATEGORY;
	}
	else {
		return INVALID;
	}

	writeToLog(LOG_EDIT_FIELD_DETERMINED);
}

//This function calls DisplayScreenConstructor class to construct the edit screen and return it as a vector<string>
vector<string> CmdEditItem::storeEditScreenForDisplay() {
	vector<string> editScreenToBeDisplayed;

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	editScreenToBeDisplayed = displayScreenConstructor->clearScreen();
	editScreenToBeDisplayed = displayScreenConstructor->constructEditScreen(_itemAddr);

	writeToLog(LOG_EDIT_SCREEN_STORED);

	return editScreenToBeDisplayed;
}

void CmdEditItem::storeSuccessMessage() {
	if(_isEditField){
		outputMessageStorage.push_back(MESSAGE_EDIT_SUCCESSFUL);

		writeToLog(LOG_SUCCESS_MESSAGE_STORED);
	}
}

void CmdEditItem::updateOutputControl() {
	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
	OutputControl::resetCurrentItemList();
	OutputControl::addItemToDisplayList(_itemAddr);

	writeToLog(LOG_OUTPUTCONTROL_UPDATED);
}

void CmdEditItem::storeCommandIntoActionLog() {
	ActionLog::addCommand(this);

	writeToLog(LOG_ACTION_LOG_UPDATED);
}

void CmdEditItem::writeToLog(string logEntry) {
	ofstream mytextfile;
	mytextfile.open(TEXT_FILE_NAME, ios::app);

	mytextfile << logEntry << endl;

	mytextfile.close();
}
