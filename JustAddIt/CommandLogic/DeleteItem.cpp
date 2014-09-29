#include "stdafx.h"
#include "DeleteItem.h"


DeleteItem::DeleteItem(vector<Item>::iterator item) {
	_item = item;
}


DeleteItem::~DeleteItem() {
}

vector<string> DeleteItem::execute() {
	deleteItem();
	displaySuccessMessage();
	return CommandLogic::outputMessageStorage;
}

void DeleteItem::deleteItem() {
	DataStorage::masterList.erase(_item);
}

void DeleteItem::displaySuccessMessage() {
	CommandLogic::outputMessageStorage.push_back("The item is successfully deleted!");
}
