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

	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
	OutputControl::resetCurrentItemList();
	OutputControl::addItemToDisplayList(_itemAddr); 

	return outputMessageStorage;
}

Item* CmdAddItem::getItem(){
	return _itemAddr;
}