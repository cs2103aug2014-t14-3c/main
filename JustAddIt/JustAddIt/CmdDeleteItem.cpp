#include "stdafx.h"
#include "CmdDeleteItem.h"


CmdDeleteItem::CmdDeleteItem(vector<Item*>::iterator itemPtr) {
	_itemPtr = itemPtr;
}

CmdDeleteItem::~CmdDeleteItem(void)
{
}

vector<string> CmdDeleteItem::execute() {
	ItemBank::deleteFromBank(_itemPtr);
	outputMessageStorage.clear();
	outputMessageStorage.push_back("Item is successfully deleted!");
	return outputMessageStorage;
}