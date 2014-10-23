#include "stdafx.h"
#include "CmdAddItem.h"

CmdAddItem::CmdAddItem(Item* item) {
	_itemAddr = item;
}

CmdAddItem::~CmdAddItem(void)
{
}

vector<string> CmdAddItem::execute() {
	if(status == CmdStatus::UNDO) {
		return CmdAddItem::undo();
	} else if (status == CmdStatus::REDO) {
		return CmdAddItem::redo();
	}
	
	ItemBank::addToBank(_itemAddr);

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructEditScreen(_itemAddr);
	outputMessageStorage.push_back("Just added it successfully!");
	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
	OutputControl::resetCurrentItemList();
	OutputControl::addItemToDisplayList(_itemAddr); 

	return outputMessageStorage;
}


vector<string> CmdAddItem::undo() {
	ItemBank::deleteFromBank(_itemAddr);

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructDeleteScreen(_itemAddr);

	return outputMessageStorage;
}

Item* CmdAddItem::getItem(){
	return _itemAddr;
}