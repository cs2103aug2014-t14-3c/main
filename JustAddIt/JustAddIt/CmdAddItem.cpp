#include "stdafx.h"
#include "CmdAddItem.h"


CmdAddItem::CmdAddItem(Item* item) {
	_itemAddr = item;
}


CmdAddItem::~CmdAddItem(void)
{
}

vector<string> CmdAddItem::execute() {
	ItemBank::addToBank(_itemAddr);
	
	CmdAddItem::constructOutput();

	return outputMessageStorage;
}

void CmdAddItem::itemToString(Item* itemPtr) {
	
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

Item* CmdAddItem::getItem(){
	return _itemAddr;
}

void CmdAddItem::setPageCommands() {
	outputMessageStorage.push_back(FORMAT_DIVIDER);

	outputMessageStorage.push_back(PAGE_COMMAND_SAVE);
	outputMessageStorage.push_back(PAGE_COMMAND_EDIT);
	outputMessageStorage.push_back(PAGE_COMMAND_CANCEL);

	outputMessageStorage.push_back(FORMAT_DIVIDER);

	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
}

void CmdAddItem::constructOutput() {
	outputMessageStorage.clear();
	OutputControl::resetCurrentItemList();

	outputMessageStorage.push_back("Item successfully added!\n");

	CmdAddItem::itemToString(_itemAddr);

	CmdAddItem::setPageCommands();
}