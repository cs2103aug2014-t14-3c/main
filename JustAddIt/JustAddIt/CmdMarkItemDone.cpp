#include "stdafx.h"
#include "CmdMarkItemDone.h"


CmdMarkItemDone::CmdMarkItemDone(vector<Item*>::iterator itemPtr) {
	_itemPtr = itemPtr;
}


CmdMarkItemDone::~CmdMarkItemDone(void)
{
}

vector<string> CmdMarkItemDone::execute() {
	ItemBank::markItemInBank(_itemPtr);
	outputMessageStorage.clear();
	outputMessageStorage.push_back("Item is successfully marked!");

	ActionLog::addCommand(this);

	return outputMessageStorage;
}