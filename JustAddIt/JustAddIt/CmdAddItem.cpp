#include "stdafx.h"
#include "CmdAddItem.h"


CmdAddItem::CmdAddItem(Item item) {
	_itemAddr = &item;
}


CmdAddItem::~CmdAddItem(void)
{
}

vector<string> CmdAddItem::execute() {
	ItemBank::addToBank(*_itemAddr);
	outputMessageStorage.clear();
	outputMessageStorage.push_back("Item successfully added!");
	return outputMessageStorage;
}