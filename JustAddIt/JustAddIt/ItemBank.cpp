//@author A0116781A
#include "stdafx.h"
#include "ItemBank.h"

vector<Item*> ItemBank::bank;
vector<Item*> ItemBank::initialBank;

void ItemBank::deleteItems(vector<Item*> itemsToDelete) {
	for(vector<Item*>::iterator iter = itemsToDelete.begin(); iter != itemsToDelete.end(); iter++) {
		deleteItem(*iter);
	}

	update();
}

bool ItemBank::isFoundForSearchingEvents(string keyword) {
	vector<Item*> events = searchEvents(keyword);
	
	if(events.size() > 0) {
		return true;
	}

	return false;
}

bool ItemBank::isFoundForSearchingDeadlines(string keyword) {
	vector<Item*> events = searchEvents(keyword);
	
	if(events.size() > 0) {
		return true;
	}

	return false;
}

bool ItemBank::isFoundForSearchingTasks(string keyword) {
	vector<Item*> events = searchEvents(keyword);
	
	if(events.size() > 0) {
		return true;
	}

	return false;
}

void ItemBank::deleteItem(Item* itemPtr) {
	bank.erase(findIter(itemPtr));
}

void ItemBank::clearBank() {
	bank.clear();
	update();
}

void ItemBank::deleteDoneItems() {
	deleteItems(getDoneItems());

	update();
}

vector<Item*> ItemBank::getDoneItems() {
	vector<Item*> doneItems;

	for(vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if((*iter)->isDone()) {
			doneItems.push_back(*iter);
		}
	}

	return doneItems;
}

void ItemBank::deleteOverdueDeadlines() {
	deleteItems(getOverdueDeadlines());

	update();
}

void ItemBank::deletePastEvents() {
	deleteItems(getPastEvents());

	update();
}

vector<Item*> ItemBank::getPastEvents() {

	vector<Item*> pastEvents;

	for(vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if(isEventPast(*iter)) {
			pastEvents.push_back(*iter);
		}
	}

	return pastEvents;
}

bool ItemBank::isEventPast(Item* itemPtr) {
	return itemPtr->isEvent() && isTimePast(itemPtr->getEndDateTime());
}

bool ItemBank::isTimePast(tm time) {
	time_t currentTime;
	std::time(&currentTime);

	return mktime(&time) <= currentTime;
}

void ItemBank::toggleItemsDone(vector<Item*> itemPtrs) {
	for(vector<Item*>::iterator iter = itemPtrs.begin(); iter != itemPtrs.end(); iter++) {
		toggleItemDone(*iter);
	}

	update();
}

void ItemBank::toggleItemDone(Item* itemPtr) {
	vector<Item*>::iterator itemIter = findIter(itemPtr);
	(*itemIter)->toggleDone();
}

void ItemBank::editItemTitle(Item* item, string newTitle) {
	vector<Item*>::iterator itemIter = findIter(item);
	(*itemIter)->setTitle(newTitle);
	update();
}

void ItemBank::editItemDescription(Item* item, string newDescription) {
	vector<Item*>::iterator itemIter = findIter(item);
	(*itemIter)->setDescription(newDescription);
	update();
}

void ItemBank::editItemStartDateTime(Item* item, tm newStartDateTime) {
	vector<Item*>::iterator itemIter = findIter(item);
	(*itemIter)->setStartDateTime(newStartDateTime);
	update();
}

void ItemBank::editItemEndDateTime(Item* item, tm newEndDateTime) {
	vector<Item*>::iterator itemIter = findIter(item);
	(*itemIter)->setEndDateTime(newEndDateTime);
	update();
}

void ItemBank::editItemVenue(Item* item, string newVenue) {
	vector<Item*>::iterator itemIter = findIter(item);
	(*itemIter)->setVenue(newVenue);
	update();
}

void ItemBank::editItemCategory(Item* item, string newCategory) {
	vector<Item*>::iterator itemIter = findIter(item);
	(*itemIter)->setCategory(newCategory);
	update();
}

void ItemBank::editItemPriority(Item* item, string newPriority) {
	vector<Item*>::iterator itemIter = findIter(item);

	if (isHighPriority(newPriority)) {
		(*itemIter)->setPriority(Item::PriorityLevel::HIGH);
	}
	else if (isMedPriority(newPriority)) {
		(*itemIter)->setPriority(Item::PriorityLevel::MED);
	}
	else if (isLowPriority(newPriority)) {
		(*itemIter)->setPriority(Item::PriorityLevel::LOW);
	}
	else {
		(*itemIter)->setPriority(Item::PriorityLevel::INVALID);
	}
	update();
}

bool ItemBank::isHighPriority(string priority) {
	return priority == "High" || priority == "H" || priority == "high" || priority == "h" || priority == "hi";
}

bool ItemBank::isMedPriority(string priority) {
	return priority == "Medium" || priority == "Med" || priority == "M" || priority == "medium" || priority == "med" || priority == "m";
}

bool ItemBank::isLowPriority(string priority) {
	return priority == "Low" || priority == "L" || priority == "low" || priority == "l";
}

bool ItemBank::searchKeyword(string itemAttribute, string keyword) {
	size_t wordPosition = itemAttribute.find(keyword);

	if (wordPosition != string::npos) {
		return true;
	}

	return false;
}

vector<Item*> ItemBank::searchEvents(string keyword) {
	vector<Item*> allEvents;
	vector<Item*> eventsFound;

	allEvents = getAllEvents();

	for (vector<Item*>::iterator iter = allEvents.begin(); iter != allEvents.end(); iter++) {
		if (searchKeyword((*iter)->getTitle(), keyword) == true) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getDescription(), keyword) == true) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getStartDateInString(), keyword) == true) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getEndDateInString(), keyword) == true) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getVenue(), keyword) == true) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getCategory(), keyword) == true) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getPriorityInString(), keyword) == true) {
			eventsFound.push_back(*iter);
		}
	}

	return eventsFound;
}

vector<Item*> ItemBank::searchDeadlines(string keyword) {
	vector<Item*> allDeadlines;
	vector<Item*> deadlinesFound;

	allDeadlines = getAllDeadlines();

	for (vector<Item*>::iterator iter = allDeadlines.begin(); iter != allDeadlines.end(); iter++) {
		if (searchKeyword((*iter)->getTitle(), keyword) == true) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getDescription(), keyword) == true) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getEndDateInString(), keyword) == true) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getVenue(), keyword) == true) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getCategory(), keyword) == true) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getPriorityInString(), keyword) == true) {
			deadlinesFound.push_back(*iter);
		}
	}

	return deadlinesFound;
}

vector<Item*> ItemBank::searchTasks(string keyword) {
	vector<Item*> allTasks;
	vector<Item*> tasksFound;

	allTasks = getAllTasks();

	for (vector<Item*>::iterator iter = allTasks.begin(); iter != allTasks.end(); iter++) {
		if (searchKeyword((*iter)->getTitle(), keyword) == true) {
			tasksFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getDescription(), keyword) == true) {
			tasksFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getVenue(), keyword) == true) {
			tasksFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getCategory(), keyword) == true) {
			tasksFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getPriorityInString(), keyword) == true) {
			tasksFound.push_back(*iter);
		}
	}

	return tasksFound;
}


vector<Item*> ItemBank::getAllTasks() {
	vector<Item*> tasks;

	for(vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if((*iter)->isTask()) {
			tasks.push_back(*iter);
		}
	}

	return tasks;
}

vector<Item*> ItemBank::getEventsThisWeek() {
	vector<Item*> eventsThisWeek;
	vector<Item*> allEvents;
	time_t currentTime;
	time(&currentTime);
	time_t timeInOneWeekTime_time_t;
	struct tm timeInOneWeekTime_struct_tm;
	localtime_s (&timeInOneWeekTime_struct_tm, &currentTime);

	timeInOneWeekTime_struct_tm.tm_mday += 7;
	timeInOneWeekTime_time_t = mktime(&(timeInOneWeekTime_struct_tm));
	localtime_s (&timeInOneWeekTime_struct_tm, &timeInOneWeekTime_time_t);

	allEvents = getAllEvents();

	for (vector<Item*>::iterator iter = allEvents.begin(); iter != allEvents.end(); iter++) {
		if (mktime(&((*iter)->getEndDateTime())) <= mktime(&(timeInOneWeekTime_struct_tm)) && 
			mktime(&((*iter)->getEndDateTime())) >= currentTime ||

			mktime(&((*iter)->getEndDateTime())) >= mktime(&(timeInOneWeekTime_struct_tm)) && 
			mktime(&((*iter)->getStartDateTime())) <= currentTime ||

			mktime(&((*iter)->getStartDateTime())) <= mktime(&(timeInOneWeekTime_struct_tm)) && 
			mktime(&((*iter)->getStartDateTime())) >= currentTime
			) {
				eventsThisWeek.push_back(*iter);
		}
	}

	return eventsThisWeek;
}

//bool ItemBank::isDateThisWeek(tm time) {
//	return time <= mktime(&(timeInOneWeekTime_struct_tm)) && 
//			mktime(&((*iter)->getStartDateTime())) >= currentTime
//}

vector<Item*> ItemBank::getAllEvents() {
	vector<Item*>events;
	time_t currentTime;
	time(&currentTime);

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->isEvent()) {
			events.push_back(*iter);
		}
	}

	return events;
}

vector<Item*> ItemBank::getDeadlinesThisWeek() {
	vector<Item*> deadlines;
	time_t currentTime;
	time(&currentTime);
	time_t timeInOneWeekTime_time_t;
	struct tm timeInOneWeekTime_struct_tm;
	localtime_s (&timeInOneWeekTime_struct_tm, &currentTime);

	timeInOneWeekTime_struct_tm.tm_mday += 7;
	timeInOneWeekTime_time_t = mktime(&(timeInOneWeekTime_struct_tm));
	localtime_s (&timeInOneWeekTime_struct_tm, &timeInOneWeekTime_time_t);

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->isDeadline() && 
			mktime(&((*iter)->getEndDateTime())) <= mktime(&(timeInOneWeekTime_struct_tm)) && 
			mktime(&((*iter)->getEndDateTime())) >= currentTime) {
				deadlines.push_back(*iter);
		}
	}

	return deadlines;
}

vector<Item*> ItemBank::getAllDeadlines() {
	vector<Item*> deadlines;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->isDeadline()) {
			deadlines.push_back(*iter);
		}
	}

	return deadlines;
}

vector<Item*> ItemBank::getOverdueDeadlines() {
	vector<Item*>overdueDeadlines;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if (isOverdue(*iter)) {
			overdueDeadlines.push_back(*iter);
		}
	}

	return overdueDeadlines;
}

bool ItemBank::isOverdue(Item* itemPtr) {
	return itemPtr->isDeadline() && isTimePast(itemPtr->getEndDateTime());
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
