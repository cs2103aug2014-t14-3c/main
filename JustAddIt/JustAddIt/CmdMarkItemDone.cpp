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

	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase->execute();
	outputMessageStorage.push_back("Item is successfully marked!");

	ActionLog::addCommand(this);

	return outputMessageStorage;
}