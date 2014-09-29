#include "stdafx.h"
#include "MarkItemDone.h"
#include "Item.h"


MarkItemDone::MarkItemDone(vector<Item>::iterator item) {
	_item = item;
}


MarkItemDone::~MarkItemDone() {

}

vector<string> MarkItemDone::execute() {
	markItem();
	displaySuccessMessage();
	return CommandLogic::outputMessageStorage;
}

void markItem() {
	//_item->_isDone = true;
}

void displaySuccessMessage() {
	CommandLogic::outputMessageStorage.push_back("Successfully marked!");
}