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

void EditItem::editTitle(string ) {
}

void EditItem::editStartDate(tm ) {
}

void EditItem::editEndDate(tm ) {
}

void EditItem::editVenue(string ) {
}

void EditItem::editCategory(vector<string> ) {
}

void EditItem::editPriority(PriorityLevel ) {
}

FIELD_TYPE EditItem::determineFieldType(string userInput) {
	if (userInput == "1") {
		return TITLE;
	}
	else if (userInput == "2") {
		return START_DATE;
	}
	else if (userInput == "3") {
		return END_DATE;
	}
	else if (userInput == "4") {
		return VENUE;
	}
	else if (userInput == "5") {
		return CATEGORY;
	}
	else if (userInput == "6") {
		return PRIORITY;
	}
	else if (userInput == "s") {
		return SAVE;
	}
	else if (userInput == "c") {
		return CANCEL;
	}
	else {
		return INVALID;
	}
}

void EditItem::executeEditFunction() {
	std::string userInput;

	do {
		cout << "command: ";
		cin >> userInput;
		FIELD_TYPE commandType = determineFieldType(userInput);

		switch (commandType) {
		case TITLE: {
			break;
					}
		case START_DATE: {
			break;
						 }
		case END_DATE: {
			break;
					   }
		case VENUE: {
			break;
					}
		case CATEGORY: {
			break;
					   }
		case PRIORITY: {
			break;
					   }
		case SAVE: {
			break;
				   }
		case CANCEL: {
			exit (0);
					 }
		case INVALID: {
			showToUser("This is an invalid input! Please enter a valid input!");
			break;
					  }
		default: {
			showToUser("The edit function has malfunctioned! Please report this issue to the developers!");
			exit (0);
				 }
		}
	} while (1);
}

void EditItem::showToUser(string outputString) {
	cout << outputString << endl;
}

void EditItem::displaySuccessMessage() {
	CommandLogic::outputMessageStorage.push_back("The item is successfully edited!");
}