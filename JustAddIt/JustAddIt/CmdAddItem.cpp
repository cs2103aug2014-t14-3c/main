#include "stdafx.h"
#include "CmdAddItem.h"

CmdAddItem::CmdAddItem(Item* item) {
	_itemAddress = item;
}

CmdAddItem::~CmdAddItem(void) {
}

vector<string> CmdAddItem::execute() {
	ItemBank::addToBank(_itemAddress);

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor -> clearScreen();
	outputMessageStorage = displayScreenConstructor -> constructEditScreen(_itemAddress);
	outputMessageStorage.push_back("Just added it successfully!");
	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
	OutputControl::resetCurrentItemList();
	OutputControl::addItemToDisplayList(_itemAddress); 

	return outputMessageStorage;
}

Item* CmdAddItem::getItem() {
	return _itemAddress;
}