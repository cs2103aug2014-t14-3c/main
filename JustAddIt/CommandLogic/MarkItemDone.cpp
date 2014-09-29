#include "stdafx.h"
#include "MarkItemDone.h"


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

void MarkItemDone::markItem() {
	_item->changeMarkedStatus();
}

void MarkItemDone::displaySuccessMessage() {
	CommandLogic::outputMessageStorage.push_back("The item is successfully marked!");
}