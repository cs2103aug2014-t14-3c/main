#include "stdafx.h"
#include "CmdDeleteItem.h"
#include "CmdHome.h"

CmdDeleteItem::CmdDeleteItem(vector<Item*> itemPtrs) {
	_itemPtrs = itemPtrs;
//	_itemAddr = *_itemPtr;
}


CmdDeleteItem::~CmdDeleteItem(void)
{
}

vector<string> CmdDeleteItem::execute() {
	ItemBank::deleteFromBank(_itemPtrs);

	Command* cmdHome = new CmdHome;
	outputMessageStorage.clear();
	outputMessageStorage = cmdHome->execute();

	outputMessageStorage.push_back("Item successfully deleted!");
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::DELETE_SCREEN);

	ActionLog::addCommand(this);

	return outputMessageStorage;
}