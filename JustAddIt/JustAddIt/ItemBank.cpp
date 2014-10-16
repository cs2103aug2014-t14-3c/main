#include "stdafx.h"
#include "ItemBank.h"

vector<Item*> ItemBank::bank;
vector<Item*> ItemBank::initialBank;

void ItemBank::addToBank(Item* item) {
	bank.push_back(item);
}

void ItemBank::deleteFromBank(vector<Item*>::iterator itemPtr) {
	bank.erase(find(bank.begin(), bank.end(), *itemPtr));
}

void ItemBank::markItemInBank(vector<Item*>::iterator itemPtr) {
	(*itemPtr)->toggleDone();
}

void ItemBank::editItemTitleInBank(vector<Item*>::iterator itemPtr, string newTitle) {
	(*itemPtr)->setTitle(newTitle);
}

void ItemBank::editItemDescriptionInBank(vector<Item*>::iterator itemPtr, string newDescription) {
	(*itemPtr)->setDescription(newDescription);
}

void ItemBank::editItemStartDateTimeInBank(vector<Item*>::iterator itemPtr, struct tm newStartDateTime) {
	//_itemPtr->setStartDate(5,5);
	//_itemPtr->setStartTime(5);
}

void ItemBank::editItemEndDateTimeInBank(vector<Item*>::iterator itemPtr, struct tm newEndDateTime) {
	//_itemPtr->setEndDate(5,5);
	//_itemPtr->setEndTime(5);
}

void ItemBank::editItemVenueInBank(vector<Item*>::iterator itemPtr, string newVenue) {
	(*itemPtr)->setVenue(newVenue);
}

void ItemBank::editItemCategoryInBank(vector<Item*>::iterator itemPtr, string newCategory) {
	(*itemPtr)->setCategory(newCategory);
}

void ItemBank::editItemPriorityInBank(vector<Item*>::iterator itemPtr, Item::PriorityLevel newPriority) {
	//itemPtr->setPriority(newPriority);
}

vector<Item*>::iterator ItemBank::findItemById(int id) {
	vector<Item*>::iterator itemPtr;

	// search vector for item with _id = id

	return itemPtr;
}

Item ItemBank::findItemByVectorPos(int i) {
	return *bank[i];
}

vector<string> ItemBank::getDeadlines(int weeks) {
	string lineContent;
	vector<string> deadlines;

	for(vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if((*iter)->getItemType() == "deadline") { // && (*iter)->getEndDateTime() x
			assert((*iter)->getEndDateInString() != "");
			lineContent = (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
			deadlines.push_back(lineContent);
		}
	}

	return deadlines;

}

vector<string> ItemBank::getTasks() {
	string lineContent;
	vector<string> tasks;

	for(vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if((*iter)->getItemType() == "task") { // && (*iter)->getEndDateTime() x
			assert((*iter)->getEndDateInString() != "");
			lineContent = (*iter)->getTitle() + " by " + (*iter)->getEndDateInString();
			tasks.push_back(lineContent);
		}
	}

	return tasks;

}

int ItemBank::getBankSize() {
	return (int)bank.size();
}

void ItemBank::initialiseBank() {
	std::copy(bank.begin(), bank.end(), initialBank.begin());
}

void ItemBank::resetBank() {
	bank.clear();
	std::copy(initialBank.begin(), initialBank.end(), bank.begin());
}