#include "stdafx.h"
#include "CmdDeleteItem.h"

CmdDeleteItem::CmdDeleteItem(vector<Item*>::iterator itemPtr) {
	_itemPtr = itemPtr;
	_itemAddr = *_itemPtr;
}

CmdDeleteItem::~CmdDeleteItem(void)
{
}

vector<string> CmdDeleteItem::execute() {
	ItemBank::deleteFromBank(_itemPtr);

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructHomeScreen();
	outputMessageStorage.push_back("Item successfully deleted!");
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::DELETE_SCREEN);
	//CmdDeleteItem::constructOutput();

	ActionLog::addCommand(this);

	return outputMessageStorage;
}

//void CmdDeleteItem::constructOutput() {
//	outputMessageStorage.clear();
//	OutputControl::resetCurrentItemList();
//
//	outputMessageStorage.push_back("Item successfully deleted!\n");
//
//	CmdDeleteItem::itemToString(_itemAddr);
//
//	CmdDeleteItem::setPageCommands();
//}

//void CmdDeleteItem::itemToString(Item* itemPtr) {
//	vector<string> item;
//	string lineContent;
//	string itemTitle = itemPtr->getTitle();
//	string itemDescription = itemPtr->getDescription();
//	string itemStartDate = itemPtr->getStartDateInString();
//	string itemEndDate = itemPtr->getEndDateInString();
//	string itemVenue = itemPtr->getVenue();
//	string itemPriority = itemPtr->getPriorityInString();
//	string itemCategory = itemPtr->getCategory();
//
//	lineContent = FORMAT_TITLE + itemTitle;
//	item.push_back(lineContent);
//
//	lineContent = FORMAT_DESCRIPTION + itemDescription;
//	item.push_back(lineContent);
//
//	lineContent = FORMAT_START + itemStartDate;
//	item.push_back(lineContent);
//
//	lineContent = FORMAT_END + itemEndDate;
//	item.push_back(lineContent);
//
//	lineContent = FORMAT_VENUE + itemVenue;
//	item.push_back(lineContent);
//
//	lineContent = FORMAT_PRIORITY + itemPriority;
//	item.push_back(lineContent);
//
//	lineContent = FORMAT_CATEGORY + itemCategory;
//	item.push_back(lineContent);
//
//	OutputControl::addItemToDisplayList(itemPtr); 
//
//	outputMessageStorage.insert(outputMessageStorage.end(), item.begin(), item.end());
//	
//	return;
//
//
////}
//
//void CmdDeleteItem::setPageCommands() {
//	outputMessageStorage.push_back(FORMAT_DIVIDER);
//
//	outputMessageStorage.push_back(PAGE_COMMAND_UNDO);
//	outputMessageStorage.push_back(PAGE_COMMAND_CALENDAR_VIEW);
//	outputMessageStorage.push_back(PAGE_COMMAND_TO_DO_LIST_VIEW);
//	outputMessageStorage.push_back(PAGE_COMMAND_OVERDUE_TASKS);
//
//	outputMessageStorage.push_back(FORMAT_DIVIDER);
//
//	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::DELETE_SCREEN);
//}