#include "stdafx.h"
#include "EditItem.h"

enum FIELD_TYPE {TITLE, START_DATE, END_DATE, VENUE, CATEGORY, PRIORITY, SAVE, CANCEL, INVALID};

EditItem::EditItem(vector<Item>::iterator item) {
	_item = item;
}


EditItem::~EditItem()
{
}

vector<string> EditItem::execute() {
	executeEditFunction();
	displaySuccessMessage();
	return CommandLogic::outputMessageStorage;
}

void EditItem::executeEditFunction() {
	std::string userCommand;

	do {
		cout << "command: ";
		cin >> userCommand;
		FIELD_TYPE commandType = determineFieldType(userCommand);

		switch (commandType) {
		case TITLE: {
			editTitle();
			break;
					}
		case START_DATE: {
			editStartDate();
			break;
						 }
		case END_DATE: {
			editEndDate();
			break;
					   }
		case VENUE: {
			editVenue();
			break;
					}
		case CATEGORY: {
			editCategory();
			break;
					   }
		case PRIORITY: {
			editPriority();
			break;
					   }
		case SAVE: {
			exit(0);
				   }
		case CANCEL: {
			//undo function
			exit (0);
					 }
		case INVALID: {
			showToUser("This is an invalid command! Please enter a valid command!");
			break;
					  }
		default: {
			showToUser("The edit function has malfunctioned! Please report this issue to the developers!");
			exit (0);
				 }
		}
	} while (1);
}

FIELD_TYPE EditItem::determineFieldType(string userCommand) {
	if (userCommand == "1") {
		return TITLE;
	}
	else if (userCommand == "2") {
		return START_DATE;
	}
	else if (userCommand == "3") {
		return END_DATE;
	}
	else if (userCommand == "4") {
		return VENUE;
	}
	else if (userCommand == "5") {
		return CATEGORY;
	}
	else if (userCommand == "6") {
		return PRIORITY;
	}
	else if (userCommand == "s") {
		return SAVE;
	}
	else if (userCommand == "c") {
		return CANCEL;
	}
	else {
		return INVALID;
	}
}

void EditItem::editTitle() {
}

void EditItem::editStartDate() {
}

void EditItem::editEndDate() {
}

void EditItem::editVenue() {
}

void EditItem::editCategory() {
}

void EditItem::editPriority() {
}

void EditItem::showToUser(string outputString) {
	cout << outputString << endl;
}

void EditItem::displaySuccessMessage() {
	CommandLogic::outputMessageStorage.push_back("The item is successfully edited!");
}