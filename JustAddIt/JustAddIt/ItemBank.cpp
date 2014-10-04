#include "stdafx.h"
#include "ItemBank.h"

vector<Item> ItemBank::bank;

void ItemBank::addToBank(Item item) {
	bank.push_back(item);
}

void ItemBank::removeFromBank(vector<Item>::iterator itemPtr) {
	bank.erase(itemPtr);
}

vector<Item>::iterator findItemById(int id) {
	vector<Item>::iterator itemPtr;

	// search vector for item with _id = id

	return itemPtr;
}