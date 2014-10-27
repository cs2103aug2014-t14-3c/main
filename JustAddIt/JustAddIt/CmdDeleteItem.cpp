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
	Command* cmdHome = new CmdHome;
	outputMessageStorage.clear();
	outputMessageStorage = cmdHome->execute();

	outputMessageStorage.push_back("Item successfully deleted!");
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::DELETE_SCREEN);

	return outputMessageStorage;
}