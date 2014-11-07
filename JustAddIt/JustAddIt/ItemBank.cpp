#include "stdafx.h"
#include "ItemBank.h"

vector<Item> ItemBank::bank;

void ItemBank::addToBank(Item item) {
	bank.push_back(item);
}

void ItemBank::removeFromBank(vector<Item>::iterator itemPtr) {
	bank.erase(itemPtr);
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

vector<Item*>::iterator ItemBank::findIter(Item* itemPtr) {
	vector<Item*>::iterator iter = bank.begin();

	while(iter != bank.end()) {
		if((*iter)->getId() == itemPtr->getId()) {
			return iter;
		}
		iter++;
	}

	throw exception("item does not exist!");
}


void ItemBank::initialiseBank() {
	vector<string> items;
	string startDateTimeInString;
	string endDateTimeInString;
	int startDateTimeInInt;
	int endDateTimeInInt;
	time_t startDateTimeInTimeT;
	time_t endDateTimeInTimeT;
	struct tm startDateTimeInStructTm;
	struct tm endDateTimeInStructTm;

	DataStorage* dataStorage = dataStorage->getInstance();
	items = dataStorage->readToBank();

	bank.clear();
	initialBank.clear();

	while (!items.empty()) {
		Item* newItem = new Item;

		//item type
		newItem->setItemType(items.back());
		items.pop_back();

		//is done
		if (items.back() != Item::IS_DONE) {
			newItem->toggleDone();
		}
		items.pop_back();

		//category
		newItem->setCategory(items.back());
		items.pop_back();

		//priority
		if (items.back() == Item::PRIORITY_HIGH) {
			newItem->setPriority(Item::PriorityLevel::HIGH);
		}
		else if (items.back() == Item::PRIORITY_MED) {
			newItem->setPriority(Item::PriorityLevel::MED);
		}
		else if (items.back() == Item::PRIORITY_LOW) {
			newItem->setPriority(Item::PriorityLevel::LOW);
		}
		else {
			newItem->setPriority(Item::PriorityLevel::INVALID);
		}
		items.pop_back();

		//venue
		newItem->setVenue(items.back());
		items.pop_back();

		//end date time
		endDateTimeInString = items.back();
		endDateTimeInInt = stol(endDateTimeInString, nullptr, 10); 
		endDateTimeInTimeT = (time_t)endDateTimeInInt;
		gmtime_s(&endDateTimeInStructTm, &endDateTimeInTimeT);
		newItem->setEndDateTime(endDateTimeInStructTm);

		items.pop_back();

		//start date time
		startDateTimeInString = items.back();
		startDateTimeInInt = stol(startDateTimeInString, nullptr, 10); 
		startDateTimeInTimeT = (time_t)startDateTimeInInt;
		gmtime_s(&startDateTimeInStructTm, &startDateTimeInTimeT);
		newItem->setStartDateTime(startDateTimeInStructTm);

		items.pop_back();

		//description
		newItem->setDescription(items.back());
		items.pop_back();

		//title
		newItem->setTitle(items.back());
		items.pop_back();

		bank.push_back(newItem);

		Item * newItemCopy = new Item;
		*newItemCopy = *newItem;
		initialBank.push_back(newItemCopy);
	}

	//deletePastEvents();

	return;
}

void ItemBank::resetBank() {
	bank.clear();
	for(vector<Item*>::iterator iter = initialBank.begin(); iter != initialBank.end(); iter++) {
		Item* itemPtr = new Item;
		*itemPtr = **iter;
		bank.push_back(itemPtr);
	}
	update();
}

bool ItemBank::addToBank(Item* item) {
	bank.push_back(item);
	update();

	return checkForConflict(item);
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
		itemsToBeWrittenToFile.push_back(to_string((*iter)->isDone()));
		itemsToBeWrittenToFile.push_back((*iter)->getItemTypeInString());
	}

	DataStorage* dataStorage = dataStorage->getInstance();
	dataStorage->writeToFile(itemsToBeWrittenToFile);

	return;
}

bool ItemBank::checkForConflict(Item* itemPtr) {
	vector<Item*>::iterator iter;
	bool isConflicted = false;

	for (iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->isEvent()) {
			if (mktime(&(itemPtr->getStartDateTime())) >= mktime(&((*iter)->getStartDateTime())) && mktime(&(itemPtr->getStartDateTime())) <= mktime(&((*iter)->getEndDateTime())) ||
				mktime(&(itemPtr->getEndDateTime())) >= mktime(&((*iter)->getStartDateTime())) && mktime(&(itemPtr->getEndDateTime())) <= mktime(&((*iter)->getEndDateTime())) ||
				mktime(&(itemPtr->getStartDateTime())) <= mktime(&((*iter)->getStartDateTime())) && mktime(&(itemPtr->getEndDateTime())) >= mktime(&((*iter)->getEndDateTime()))) {
					isConflicted = true;
			}
		}
	}

	return isConflicted;
}

