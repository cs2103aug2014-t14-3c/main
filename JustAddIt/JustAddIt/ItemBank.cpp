#include "stdafx.h"
#include "ItemBank.h"

vector<Item*> ItemBank::bank;
vector<Item*> ItemBank::initialBank;

void ItemBank::addToBank(Item* item) {
	bank.push_back(item);
	update();
}

void ItemBank::deleteFromBank(vector<Item*> itemPtr) {
	vector<Item*>::iterator myIter;
	myIter = itemPtr.begin();
	while(myIter!=itemPtr.end()){
		bank.erase(find(bank.begin(), bank.end(), *myIter));
		myIter++;
	}
	update();
}

void ItemBank::deleteAllDoneItemsFromBank() {
	vector<Item*>::iterator iter;
	bool allDoneItemsDeleted = false;

	while (allDoneItemsDeleted == false) {
		allDoneItemsDeleted = true;
		for(iter = bank.begin(); iter != bank.end(); iter++) {
			if ((*iter)->getIsDone() == true) {
				bank.erase(iter);
				allDoneItemsDeleted = false;
			}
			else {
				continue;
			}
		}
	}
}

void ItemBank::deleteAllOverdueDeadlinesFromBank() {
	vector<Item*>::iterator iter;
	bool allOverdueDeadlinesDeleted = false;
	time_t currentTime;
	time(&currentTime);

	while (allOverdueDeadlinesDeleted == false) {
		allOverdueDeadlinesDeleted = true;
		for(iter = bank.begin(); iter != bank.end(); iter++) {
			if ((*iter)->getItemType() == "deadline" && mktime(&((*iter)->getEndDateTime())) <= currentTime) {
				bank.erase(iter);
				allOverdueDeadlinesDeleted = false;
			}
			else {
				continue;
			}
		}
	}
}

void ItemBank::markItemsInBank(vector<Item*> itemPtr) {

	vector<Item*>::iterator myIter;
	myIter = itemPtr.begin();
	while(myIter!=itemPtr.end()){
		(*myIter)->toggleDone();
		myIter++;
	}
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

void ItemBank::editItemStartDateTimeInBank(vector<Item*>::iterator itemPtr, tm newStartDateTime) {
	(*itemPtr)->setStartDateTime(newStartDateTime);
}

void ItemBank::editItemEndDateTimeInBank(vector<Item*>::iterator itemPtr, tm newEndDateTime) {
	(*itemPtr)->setEndDateTime(newEndDateTime);
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
	if (newPriority == "High" || newPriority == "H" || newPriority == "high" || newPriority == "h" || newPriority == "hi") {
		(*itemPtr)->setPriority(static_cast<Item::PriorityLevel>(2));
	}
	else if (newPriority == "Medium" || newPriority == "Med" || newPriority == "M" || newPriority == "medium" || newPriority == "med" || newPriority == "m") {
		(*itemPtr)->setPriority(static_cast<Item::PriorityLevel>(1));
	}
	else if (newPriority == "Low" || newPriority == "L" || newPriority == "low" || newPriority == "l") {
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

vector<Item*> ItemBank::getEvents(struct tm cutOffDateTime) {
	vector<Item*>eventsToBeDisplayed;
	time_t currentTime;
	time(&currentTime);

	assert(mktime(&(cutOffDateTime)) >= currentTime);

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->getItemType() == "event" && mktime(&((*iter)->getEndDateTime())) <= mktime(&(cutOffDateTime)) && mktime(&((*iter)->getEndDateTime())) >= currentTime) {
			eventsToBeDisplayed.push_back(*iter);
		}
		else {
			continue;
		}
	}

	return eventsToBeDisplayed;
}

vector<Item*> ItemBank::getDeadlines(struct tm cutOffDateTime) {
	vector<Item*>deadlinesToBeDisplayed;
	time_t currentTime;
	time(&currentTime);

	assert(mktime(&(cutOffDateTime)) >= currentTime);

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->getItemType() == "deadline" && mktime(&((*iter)->getEndDateTime())) <= mktime(&(cutOffDateTime)) && mktime(&((*iter)->getEndDateTime())) >= currentTime) {
			deadlinesToBeDisplayed.push_back(*iter);
		}
		else {
			continue;
		}
	}

	return deadlinesToBeDisplayed;
}

vector<Item*> ItemBank::getAllEvents() {
	vector<Item*>eventsToBeDisplayed;
	time_t currentTime;
	time(&currentTime);

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->getItemType() == "event") {
			eventsToBeDisplayed.push_back(*iter);
		}
		else {
			continue;
		}
	}

	return eventsToBeDisplayed;
}

vector<Item*> ItemBank::getAllDeadlines() {
	vector<Item*>deadlinesToBeDisplayed;
	time_t currentTime;
	time(&currentTime);

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->getItemType() == "deadline") {
			deadlinesToBeDisplayed.push_back(*iter);
		}
		else {
			continue;
		}
	}

	return deadlinesToBeDisplayed;
}

vector<Item*> ItemBank::getTasks() {
	vector<Item*> tasksToBeDisplayed;

	for(vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if((*iter)->getItemType() == "task") {
			assert((*iter)->getTitle() != "");
			tasksToBeDisplayed.push_back(*iter);
		}
		else {
			continue;
		}
	}

	return tasksToBeDisplayed;
}

vector<Item*> ItemBank::getOverdueDeadlines() {
	vector<Item*>overdueDeadlinesToBeDisplayed;
	vector<Item*>::iterator iter;

	time_t currentTime;
	time(&currentTime);

	for (iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->getItemType() == "deadline" && mktime(&((*iter)->getEndDateTime())) <= currentTime) {
			overdueDeadlinesToBeDisplayed.push_back(*iter);
		}
		else {
			continue;
		}
	}

	return overdueDeadlinesToBeDisplayed;
}

bool ItemBank::searchKeywordInItemAttribute(string itemAttribute, string keyword) {
	bool isFound = false;

	size_t wordPosition = itemAttribute.find(keyword);
	if (wordPosition != string::npos) {
		isFound = true;
	}

	return isFound;
}

vector<Item*> ItemBank::searchEvents(string keyword) {
	vector<Item*> eventsToBeDisplayed;
	bool isFound = false;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->getItemType() == "event") {

			if (searchKeywordInItemAttribute((*iter)->getTitle(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getDescription(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getStartDateInString(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getEndDateInString(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getVenue(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getCategory(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getPriorityInString(), (keyword.substr(1))) == true) {
				isFound = true;
			}

			if (isFound == true) {
				eventsToBeDisplayed.push_back(*iter);
			}

			isFound = false;
		}
	}

	return eventsToBeDisplayed;
}

vector<Item*> ItemBank::searchDeadlines(string keyword) {
	vector<Item*> deadlinesToBeDisplayed;
	bool isFound = false;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->getItemType() == "deadline") {
			if (searchKeywordInItemAttribute((*iter)->getTitle(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getDescription(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getEndDateInString(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getVenue(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getCategory(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getPriorityInString(), (keyword.substr(1))) == true) {
				isFound = true;
			}

			if (isFound == true) {
				deadlinesToBeDisplayed.push_back(*iter);
			}

			isFound = false;
		}
	}

	return deadlinesToBeDisplayed;
}

vector<Item*> ItemBank::searchTasks(string keyword) {
	vector<Item*> tasksToBeDisplayed;
	bool isFound = false;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->getItemType() == "task") {

			if (searchKeywordInItemAttribute((*iter)->getTitle(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getDescription(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getVenue(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getCategory(), (keyword.substr(1))) == true) {
				isFound = true;
			}
			if (searchKeywordInItemAttribute((*iter)->getPriorityInString(), (keyword.substr(1))) == true) {
				isFound = true;
			}

			if (isFound == true) {
				tasksToBeDisplayed.push_back(*iter);
			}

			isFound = false;
		}
	}

	return tasksToBeDisplayed;
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
	}

	return;
}

void ItemBank::resetBank() {
	bank.clear();
	std::copy(initialBank.begin(), initialBank.end(), bank.begin());
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