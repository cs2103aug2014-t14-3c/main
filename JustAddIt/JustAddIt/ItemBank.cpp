#include "stdafx.h"
#include "ItemBank.h"

vector<Item> ItemBank::bank;

void ItemBank::addToBank(Item item) {
	bank.push_back(item);
}

void ItemBank::deleteFromBank(vector<Item>::iterator itemPtr) {
	bank.erase(itemPtr);
}

void ItemBank::markItemInBank(vector<Item>::iterator itemPtr) {
	itemPtr->toggleDone();
}

vector<Item>::iterator ItemBank::findItemById(int id) {
	vector<Item>::iterator itemPtr;

	// search vector for item with _id = id

	return itemPtr;
}

Item ItemBank::findItemByVectorPos(int i) {
	return bank[i];
}

int ItemBank::getBankSize() {
	return (int)bank.size();
}