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

void ItemBank::editItemTitleInBank(vector<Item>::iterator itemPtr, string newTitle) {
	itemPtr->setTitle(newTitle);
}

void ItemBank::editItemStartDateTimeInBank(vector<Item>::iterator itemPtr, struct tm newStartDateTime) {
	//_itemPtr->setStartDate(5,5);
	//_itemPtr->setStartTime(5);
}

void ItemBank::editItemEndDateTimeInBank(vector<Item>::iterator itemPtr, struct tm newEndDateTime) {
	//_itemPtr->setEndDate(5,5);
	//_itemPtr->setEndTime(5);
}

void ItemBank::editItemVenueInBank(vector<Item>::iterator itemPtr, string newVenue) {
	itemPtr->setVenue(newVenue);
}

void ItemBank::editItemCategoryInBank(vector<Item>::iterator itemPtr, string newCategory) {
	itemPtr->setCategory(newCategory);
}

void ItemBank::editItemPriorityInBank(vector<Item>::iterator itemPtr, PriorityLevel newPriority) {
	//itemPtr->setPriority(newPriority);
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