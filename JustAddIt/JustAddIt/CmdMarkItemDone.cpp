#include "stdafx.h"
#include "CmdMarkItemDone.h"


CmdMarkItemDone::CmdMarkItemDone(vector<Item*> itemPtr) {
	_itemPtr = itemPtr;
}


CmdMarkItemDone::~CmdMarkItemDone(void)
{
}

vector<string> CmdMarkItemDone::execute() {
	ItemBank::markItemsInBank(_itemPtr);
	outputMessageStorage.clear();
	outputMessageStorage.push_back("Item is successfully marked!");
	return outputMessageStorage;
}