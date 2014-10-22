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

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructEditScreen(_itemAddr);
	outputMessageStorage.push_back("Just added it successfully!");
	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
	OutputControl::resetCurrentItemList();
	OutputControl::addItemToDisplayList(_itemAddr); 

	ActionLog::addCommand(this);

	return outputMessageStorage;
}

Item* CmdAddItem::getItem(){
	return _itemAddr;
}