//@author A0128461H
#include "stdafx.h"
#include "CmdAddItem.h"

const string CmdAddItem::SUCCESS_MESSAGE = "Just added it successfully!";
const string CmdAddItem::TIME_DATE_CONFLICT_MESSAGE = "This conflicts with another event!";

CmdAddItem::CmdAddItem(Item* item) {
	_itemAddress = item;
}

CmdAddItem::~CmdAddItem(void) {
}

vector<string> CmdAddItem::execute() {
	bool isTimeOrDateConflicted = ItemBank::getInstance() -> addToBank(_itemAddress);
	assert(_itemAddress != NULL);

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor -> clearScreen();
	outputMessageStorage = displayScreenConstructor -> constructEditScreen(_itemAddress);
	outputMessageStorage.push_back(SUCCESS_MESSAGE);

	if (isTimeOrDateConflicted == true) {
		outputMessageStorage.push_back(TIME_DATE_CONFLICT_MESSAGE);
	}

	OutputControl::setCurrentScreen(OutputControl::EDIT_SCREEN);
	OutputControl::resetCurrentItemList();
	OutputControl::addItemToDisplayList(_itemAddress); 

	ActionLog::addCommand(this);

	return outputMessageStorage;
}

Item* CmdAddItem::getItem() {
	return _itemAddress;
}