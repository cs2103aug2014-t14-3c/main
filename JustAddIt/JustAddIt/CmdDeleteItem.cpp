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
	if(status == CmdStatus::UNDO) {
		return CmdDeleteItem::undo(); 
	} else if (status == CmdStatus::REDO) {
		return CmdDeleteItem::redo();
	}

	ItemBank::deleteMultipleItemsFromBank(_itemPtrs);

	Command* cmdHome = new CmdHome;
	outputMessageStorage.clear();
	outputMessageStorage = cmdHome->execute();

	outputMessageStorage.push_back("Item successfully deleted!");
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::DELETE_SCREEN);

	return outputMessageStorage;
}

vector<string> CmdDeleteItem::undo() {
	for(vector<Item*>::iterator iter = _itemPtrs.begin(); iter != _itemPtrs.end(); iter++) {
		ItemBank::addToBank(*iter);
	}
	

	return outputMessageStorage;
}