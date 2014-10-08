#include "stdafx.h"
#include "CmdEditItem.h"


CmdEditItem::CmdEditItem(vector<Item*>::iterator itemPtr, int fieldNum, string newFieldInfo) {
	_itemPtr = itemPtr;
	_editFieldNumber = fieldNum;
	_newFieldInfo = newFieldInfo;
	//string _newTitle = NULL;
	//string _newDescription;
	////struct tm _newStartDateTime = NULL;
	////struct tm _newEndDateTime = NULL;
	//string _newVenue = NULL;
	//string _newCategory = NULL;
	////PriorityLevel _newPriority = NULL;
}


CmdEditItem::~CmdEditItem(void)
{
}

vector<string> CmdEditItem::execute() {

	switch (_editFieldNumber) {
	case 1: {
		ItemBank::editItemTitleInBank(_itemPtr, _newFieldInfo);
		break;
			}
	case 2: {
		ItemBank::editItemDescriptionInBank(_itemPtr, _newFieldInfo);
		break;

			}
	case 3: {
		//TODO: convert field info to date/time
		//ItemBank::editItemStartDateTimeInBank(_itemPtr, _newStartDateTime);
		//break;

			}
	case 4: {
		//TODO: convert field info to date/time
		//ItemBank::editItemEndDateTimeInBank(_itemPtr, _newEndDateTime);
		//break;

			}
	case 5: {
		ItemBank::editItemVenueInBank(_itemPtr, _newFieldInfo);
		break;

			}
	case 6: {
		ItemBank::editItemCategoryInBank(_itemPtr, _newFieldInfo);
		break;

			}
	case 7: {
		//ItemBank::editItemPriorityInBank(_itemPtr, _newPriority);
		//break;
			}
	default: {
		outputMessageStorage.push_back("An error has occcurred!");
			 }
	}

	CmdEditItem::constructOutput();

	return outputMessageStorage;
}

void CmdEditItem::setPageCommands() {
	outputMessageStorage.push_back(FORMAT_DIVIDER);

	outputMessageStorage.push_back(PAGE_COMMAND_SAVE);
	outputMessageStorage.push_back(PAGE_COMMAND_EDIT);
	outputMessageStorage.push_back(PAGE_COMMAND_CANCEL);

	outputMessageStorage.push_back(FORMAT_DIVIDER);

	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
}

void CmdEditItem::constructOutput() {
	outputMessageStorage.clear();
	
	outputMessageStorage.push_back("Item successfully edited!\n");

	//
	CmdEditItem::itemToString(*_itemPtr);

	CmdEditItem::setPageCommands();
}

void CmdEditItem::itemToString(Item* itemPtr) {
	
	vector<string> item;
	string lineContent;
	string itemTitle = itemPtr->getTitle();
	string itemDescription = itemPtr->getDescription();
	string itemStartDate = itemPtr->getStartDateInString();
	string itemEndDate = itemPtr->getEndDateInString();
	string itemVenue = itemPtr->getVenue();
	string itemPriority = itemPtr->getPriorityInString();
	string itemCategory = itemPtr->getCategory();

	lineContent = "1) " + FORMAT_TITLE + itemTitle;
	item.push_back(lineContent);

	lineContent = "2) " + FORMAT_DESCRIPTION + itemDescription;
	item.push_back(lineContent);

	lineContent = "3) " + FORMAT_START + itemStartDate;
	item.push_back(lineContent);

	lineContent = "4) " +FORMAT_END + itemEndDate;
	item.push_back(lineContent);

	lineContent = "5) " + FORMAT_VENUE + itemVenue;
	item.push_back(lineContent);

	lineContent = "6) " + FORMAT_PRIORITY + itemPriority;
	item.push_back(lineContent);

	lineContent = "7) " + FORMAT_CATEGORY + itemCategory;
	item.push_back(lineContent);

	OutputControl::addItemToDisplayList(itemPtr); 

	outputMessageStorage.insert(outputMessageStorage.end(), item.begin(), item.end());
	
	return;
}