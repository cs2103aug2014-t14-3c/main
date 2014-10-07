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
	
	outputMessageStorage.clear();
	
	outputMessageStorage.push_back("Item successfully added!\n");

	itemToString(_itemAddr);

	outputMessageStorage.push_back(FORMAT_DIVIDER);

	outputMessageStorage.push_back(PAGE_COMMAND_SAVE);
	outputMessageStorage.push_back(PAGE_COMMAND_EDIT);
	outputMessageStorage.push_back(PAGE_COMMAND_CANCEL);

	outputMessageStorage.push_back(FORMAT_DIVIDER);

	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);

	return outputMessageStorage;
}

Item* CmdAddItem::getItem(){
	return _itemAddr;
}
