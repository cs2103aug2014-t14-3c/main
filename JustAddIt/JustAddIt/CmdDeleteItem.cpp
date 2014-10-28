#include "stdafx.h"
#include "CmdDeleteItem.h"

CmdDeleteItem::CmdDeleteItem(vector<Item*> itemPtrs) {
	_itemPtrs = itemPtrs;

}


CmdDeleteItem::~CmdDeleteItem(void)
{
}

vector<string> CmdDeleteItem::execute() {
	ItemBank::deleteFromBank(_itemPtrs);


	//returns to base screen
	Command* cmdBase = new CmdGoToBaseScreen(OutputControl::getCurrentBaseScreen());
	outputMessageStorage.clear();
	outputMessageStorage = cmdBase->execute();

	outputMessageStorage.push_back("Item successfully deleted!");
	

	ActionLog::addCommand(this);

	return outputMessageStorage;
}