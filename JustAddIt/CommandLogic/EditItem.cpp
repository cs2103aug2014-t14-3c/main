#include "stdafx.h"
#include "EditItem.h"

// enum PRIORITY_LEVEL { LOW, MED, HIGH, PRIORITY_LEVEL_INVALID}; NOTE: Already defined in Item.h

EditItem::EditItem(vector<Item>::iterator item) {
	_item = item;
}

EditItem::~EditItem()
{
}

vector<string> EditItem::execute() {
	displayEditScreen();
	executeEditFunction();
	displaySuccessMessage();
	return CommandLogic::outputMessageStorage;
}

void EditItem::executeEditFunction() {
	std::string userCommand;

	do {
		cout << "command: ";
		cin >> userCommand;
		COMMAND_TYPE commandType = determineCommandType(userCommand);

		switch (commandType) {
		case EDIT_TITLE: {
			editTitle();
			displayEditScreen();
			break;
						 }
		case EDIT_START_DATE: {
			editStartDate();
			displayEditScreen();
			break;
							  }
		case EDIT_END_DATE: {
			editEndDate();
			displayEditScreen();
			break;
							}
		case EDIT_VENUE: {
			editVenue();
			displayEditScreen();
			break;
						 }
		case EDIT_CATEGORY: {
			editCategory();
			displayEditScreen();
			break;
							}
		case EDIT_PRIORITY: {
			editPriority();
			displayEditScreen();
			break;
							}
		case SAVE: {
			exit(0);
				   }
		case CANCEL: {
			//call for undo function????ARE WE GOING TO HAVE THIS FUNCTION? OR WILL THE UNDO COMMAND BE A OPTION?
			exit (0);
					 }
		case COMMAND_INVALID: {
			showToUser("This is an invalid command! Please refer to the command prompt for all the commands available!");
			break;
							  }
		default: {
			showToUser("The edit function has malfunctioned! Please report this issue to the developers!");
			exit (0);
				 }
		}
	} while (1);

	return;
}

COMMAND_TYPE EditItem::determineCommandType(string userCommand) {
	if (userCommand == "e1") {
		return EDIT_TITLE;
	}
	else if (userCommand == "e2") {
		return EDIT_START_DATE;
	}
	else if (userCommand == "e3") {
		return EDIT_END_DATE;
	}
	else if (userCommand == "e4") {
		return EDIT_VENUE;
	}
	else if (userCommand == "e5") {
		return EDIT_CATEGORY;
	}
	else if (userCommand == "e6") {
		return EDIT_PRIORITY;
	}
	else if (userCommand == "s") {
		return SAVE;
	}
	else if (userCommand == "c") {
		return CANCEL;
	}
	else {
		return COMMAND_INVALID;
	}
}

void EditItem::editTitle() {
	string newTitle;
	cin >> newTitle;
	_item->setTitle(newTitle);
}

void EditItem::editStartDate() {
	tm newStartDate;
	time_t temp = time(0);

	newStartDate = *(localtime(&temp));
	
	//cin >> newStartDate;
	//need to find some way to take in the user input and store it as a tm variable
	_item->setStartDate(newStartDate);
}

void EditItem::editEndDate() {
	tm newEndDate;
	time_t temp = time(0);

	newEndDate = *(localtime(&temp));

	//cin >> newEndDate;
	//same problem as above
	_item->setEndDate(newEndDate);
}

void EditItem::editVenue() {
	string newVenue;
	cin >> newVenue;
	_item->setVenue(newVenue);
}

void EditItem::editCategory() {
	string newCategory;
	cin >> newCategory;
	_item->setCategory(newCategory);
}

void EditItem::editPriority() {
	_item->setPriority(obtainNewPriorityLevel());
}

PRIORITY_LEVEL EditItem::obtainNewPriorityLevel() {
	string userNewPriorityInput;

	do {
		cin >> userNewPriorityInput;
		if (userNewPriorityInput == "LOW" || "Low" || "low" || "L" || "l") {
			return LOW;
		}
		else if (userNewPriorityInput == "MEDIUM" || "Medium" || "medium" || "MED" || "Med" || "med" || "M" || "m") {
			return MED;
		}
		else if (userNewPriorityInput == "HIGH" || "High" || "high" || "H" || "h") {
			return HIGH;
		}
		else {
			showToUser("This is an invalid priority level! Please type in either HIGH, MEDIUM OR LOW!");
			showToUser("Priority Level: ");
			break;
		}
	} while (1);
}

void EditItem::showToUser(string outputString) {
	cout << outputString << endl;
}

void EditItem::displaySuccessMessage() {
	CommandLogic::outputMessageStorage.push_back("The item is successfully edited!");
}

void EditItem::displayEditScreen() {
	_item->getTitle();
	_item->getStartDate();
	_item->getEndDate();
	_item->getVenue();
	_item->getCategories();
	_item->getPriority();

}
