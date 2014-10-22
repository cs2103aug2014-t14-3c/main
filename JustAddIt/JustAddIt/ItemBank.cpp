#include "stdafx.h"
#include "ItemBank.h"

vector<Item*> ItemBank::bank;
vector<Item*> ItemBank::initialBank;

void ItemBank::addToBank(Item* item) {
	bank.push_back(item);
	update();
}

void ItemBank::deleteFromBank(vector<Item*>::iterator itemPtr) {
	bank.erase(find(bank.begin(), bank.end(), *itemPtr));
	update();
}

void ItemBank::markItemInBank(vector<Item*>::iterator itemPtr) {
	(*itemPtr)->toggleDone();
	update();
}

void ItemBank::editItemTitleInBank(vector<Item*>::iterator itemPtr, string newTitle) {
	(*itemPtr)->setTitle(newTitle);
	update();
}

void ItemBank::editItemDescriptionInBank(vector<Item*>::iterator itemPtr, string newDescription) {
	(*itemPtr)->setDescription(newDescription);
	update();
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
	update();
}

void ItemBank::editItemCategoryInBank(vector<Item*>::iterator itemPtr, string newCategory) {
	(*itemPtr)->setCategory(newCategory);
	update();
}

void ItemBank::editItemPriorityInBank(vector<Item*>::iterator itemPtr, string newPriority) {
	if (newPriority == "High" || "H" || "high" || "h" || "hi") {
		(*itemPtr)->setPriority(static_cast<Item::PriorityLevel>(2));
	}
	else if (newPriority == "Medium" || "Med" || "M" || "medium" || "med" || "m") {
		(*itemPtr)->setPriority(static_cast<Item::PriorityLevel>(1));
	}
	else if (newPriority == "Low" || "L" || "low" || "l") {
		(*itemPtr)->setPriority(static_cast<Item::PriorityLevel>(0));
	}
	else {
		(*itemPtr)->setPriority(static_cast<Item::PriorityLevel>(3));
	}
	return;
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
			assert((*iter)->getTitle() != "");
			lineContent = (*iter)->getTitle();
			tasks.push_back(lineContent);
		}
	}

	return tasks;

}

int ItemBank::getBankSize() {
	return (int)bank.size();
}

void ItemBank::initialiseBank() {
	vector<string>itemsToBeReadToBank;
	string startDateTimeInStringForm;
	string endDateTimeInStringForm;
	int startDateTimeInIntForm;
	int endDateTimeInIntForm;
	time_t startDateTimeInTimeTForm;
	time_t endDateTimeInTimeTForm;
	struct tm startDateTimeInStructTmForm;
	struct tm endDateTimeInStructTmForm;

	DataStorage* dataStorage = dataStorage->getInstance();
	itemsToBeReadToBank = dataStorage->readToBank();

	bank.clear();
	initialBank.clear();
	while (!itemsToBeReadToBank.empty()) {
		Item* newItem = new Item;

		//item type
		newItem->setItemType(itemsToBeReadToBank.back());
		itemsToBeReadToBank.pop_back();

		//is done
		if (itemsToBeReadToBank.back() != "0") {
			newItem->toggleDone();
		}
		itemsToBeReadToBank.pop_back();

		//category
		newItem->setCategory(itemsToBeReadToBank.back());
		itemsToBeReadToBank.pop_back();

		//priority
		if (itemsToBeReadToBank.back() == "High") {
			newItem->setPriority(static_cast<Item::PriorityLevel>(2));
		}
		else if (itemsToBeReadToBank.back() == "Medium") {
			newItem->setPriority(static_cast<Item::PriorityLevel>(1));
		}
		else if (itemsToBeReadToBank.back() == "Low") {
			newItem->setPriority(static_cast<Item::PriorityLevel>(0));
		}
		else {
			newItem->setPriority(static_cast<Item::PriorityLevel>(3));
		}
		itemsToBeReadToBank.pop_back();

		//venue
		newItem->setVenue(itemsToBeReadToBank.back());
		itemsToBeReadToBank.pop_back();

		//end date time
		endDateTimeInStringForm = itemsToBeReadToBank.back();
		endDateTimeInIntForm = stol(endDateTimeInStringForm, nullptr, 10); 
		endDateTimeInTimeTForm = (time_t)endDateTimeInIntForm;
		gmtime_s(&endDateTimeInStructTmForm, &endDateTimeInTimeTForm);
		newItem->setEndDateTime(endDateTimeInStructTmForm);

		itemsToBeReadToBank.pop_back();

		//start date time
		startDateTimeInStringForm = itemsToBeReadToBank.back();
		startDateTimeInIntForm = stol(startDateTimeInStringForm, nullptr, 10); 
		startDateTimeInTimeTForm = (time_t)startDateTimeInIntForm;
		gmtime_s(&startDateTimeInStructTmForm, &startDateTimeInTimeTForm);
		newItem->setStartDateTime(startDateTimeInStructTmForm);

		itemsToBeReadToBank.pop_back();

		//description
		newItem->setDescription(itemsToBeReadToBank.back());
		itemsToBeReadToBank.pop_back();

		//title
		newItem->setTitle(itemsToBeReadToBank.back());
		itemsToBeReadToBank.pop_back();

		bank.push_back(newItem);
		initialBank.push_back(newItem);
	}

	return;
}

void ItemBank::resetBank() {
	bank.clear();

	for(vector<Item*>::iterator iter = initialBank.begin(); iter != initialBank.end(); iter++) {
		bank.push_back(*iter);
	}
}

void ItemBank::update() {
	vector<string>itemsToBeWrittenToFile;
	vector<Item*>::iterator iter;
	string dummyString;

	for (iter = bank.begin(); iter != bank.end(); iter++) {
		itemsToBeWrittenToFile.push_back((*iter)->getTitle());
		itemsToBeWrittenToFile.push_back((*iter)->getDescription());
		itemsToBeWrittenToFile.push_back(to_string(mktime(&((*iter)->getStartDateTime()))));
		itemsToBeWrittenToFile.push_back(to_string(mktime(&((*iter)->getEndDateTime()))));
		itemsToBeWrittenToFile.push_back((*iter)->getVenue());
		itemsToBeWrittenToFile.push_back((*iter)->getPriorityInString());
		itemsToBeWrittenToFile.push_back((*iter)->getCategory());
		itemsToBeWrittenToFile.push_back(to_string((*iter)->getIsDone()));
		itemsToBeWrittenToFile.push_back((*iter)->getItemType());
	}

	DataStorage* dataStorage = dataStorage->getInstance();
	dataStorage->writeToFile(itemsToBeWrittenToFile);

	return;
}