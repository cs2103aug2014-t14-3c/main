//@author A0116781A
#include "stdafx.h"
#include "ItemBank.h"

//private attributes and methods

ItemBank* ItemBank::itemBank = NULL;
bool ItemBank::instanceFlag = false;

vector<Item*> ItemBank::initialBank;
vector<Item*> ItemBank::bank;

ItemBank::ItemBank() {
	sevenDaysInSeconds = 604800;
}

ItemBank::~ItemBank() {
	instanceFlag = false;
}

ItemBank* ItemBank::getInstance() {
	if(!instanceFlag) {
		ItemBank();
		instanceFlag = true;
	}
	
	return itemBank;
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

void ItemBank::deleteItem(Item* itemPtr) {
	bank.erase(findIter(itemPtr));
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

bool ItemBank::isTimePast(tm time) {
	time_t currentTime;
	std::time(&currentTime);

	return mktime(&time) <= currentTime;
}

bool ItemBank::isDateThisWeek(tm timeInTm) {
	time_t currentTime;
	std::time(&currentTime);
	time_t oneWeekLaterTime = currentTime + sevenDaysInSeconds;
	time_t givenTime = mktime(&timeInTm);


	return givenTime <= oneWeekLaterTime && givenTime >= currentTime;
}

bool ItemBank::isDateAfterThisWeek(tm timeInTm) {
	time_t oneWeekLaterTime;
	std::time(&oneWeekLaterTime);
	oneWeekLaterTime += sevenDaysInSeconds;
	time_t givenTime = mktime(&timeInTm);


	return givenTime >= oneWeekLaterTime;
}

bool ItemBank::isThisWeekInPeriod(tm timeStart, tm timeEnd) {
	if(isDateThisWeek(timeStart) || isDateThisWeek(timeEnd)) {
		return true;
	}
	if(isTimePast(timeStart) && isDateAfterThisWeek(timeEnd)) {
		return true;
	}

	return false;
}

bool ItemBank::isEventPast(Item* itemPtr) {
	return itemPtr->isEvent() && isTimePast(itemPtr->getEndDateTime());
}

bool ItemBank::isOverdue(Item* itemPtr) {
	return itemPtr->isDeadline() && isTimePast(itemPtr->getEndDateTime());
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

void ItemBank::toggleItemDone(Item* itemPtr) {
	vector<Item*>::iterator itemIter = findIter(itemPtr);
	(*itemIter)->toggleDone();
}

void ItemBank::update() {
	vector<string>items;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		items = updateItem(items, *iter);
	}
	
	DataStorage* dataStorage = dataStorage->getInstance();
	dataStorage->writeToFile(items);

	return;
}

vector<string> ItemBank::updateItem(vector<string> items, Item* item) {
	items.push_back(item->getTitle());
	items.push_back(item->getDescription());
	items.push_back(to_string(item->getStartDateTime_T()));
	items.push_back(to_string(item->getEndDateTime_T()));
	items.push_back(item->getVenue());
	items.push_back(item->getPriorityInString());
	items.push_back(item->getCategory());
	items.push_back(to_string(item->isDone()));
	items.push_back(item->getItemTypeInString());

	return items;
}

//public attributes and methods

void ItemBank::initialiseBank() {
	vector<string> items;

	DataStorage* dataStorage = dataStorage->getInstance();
	items = dataStorage->readToBank();

	bank.clear();
	initialBank.clear();

	vector<string>::iterator iter = items.begin();

	while (iter != items.end()) {
		Item* newItem = new Item;

		iter = newItem->strToItem(iter);

		bank.push_back(newItem);

		Item * newItemCopy = new Item;
		*newItemCopy = *newItem;
		initialBank.push_back(newItemCopy);
	}

	items.clear();

	//deletePastEvents();

	return;
}

void ItemBank::resetBank() {
	bank.clear();
	for(vector<Item*>::iterator iter = initialBank.begin(); iter != initialBank.end(); iter++) {
		Item* itemPtr = new Item;
		*itemPtr = **iter;
		addToBank(itemPtr);
	}
}

bool ItemBank::addToBank(Item* item) {
	bank.push_back(item);
	update();

	return checkForConflict(item);
}

int ItemBank::getNumberOfMarkedItems() {
	vector<Item*> markedDone = getDoneItems();

	return (int)markedDone.size();
}

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

void ItemBank::clearBank() {
	bank.clear();
	update();
}

void ItemBank::deleteDoneItems() {
	deleteItems(getDoneItems());

	update();
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

void ItemBank::toggleItemsDone(vector<Item*> itemPtrs) {
	for(vector<Item*>::iterator iter = itemPtrs.begin(); iter != itemPtrs.end(); iter++) {
		toggleItemDone(*iter);
	}

	update();
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
		if (searchKeyword((*iter)->getTitle(), keyword)) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getDescription(), keyword)) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getStartDateInString(), keyword)) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getEndDateInString(), keyword)) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getVenue(), keyword)) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getCategory(), keyword)) {
			eventsFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getPriorityInString(), keyword)) {
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
		if (searchKeyword((*iter)->getTitle(), keyword)) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getDescription(), keyword)) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getEndDateInString(), keyword)) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getVenue(), keyword)) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getCategory(), keyword)) {
			deadlinesFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getPriorityInString(), keyword)) {
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
		if (searchKeyword((*iter)->getTitle(), keyword)) {
			tasksFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getDescription(), keyword)) {
			tasksFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getVenue(), keyword)) {
			tasksFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getCategory(), keyword)) {
			tasksFound.push_back(*iter);
		} else if (searchKeyword((*iter)->getPriorityInString(), keyword)) {
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

	allEvents = getAllEvents();

	for (vector<Item*>::iterator iter = allEvents.begin(); iter != allEvents.end(); iter++) {
		if (isThisWeekInPeriod((*iter)->getStartDateTime(), (*iter)->getEndDateTime())) {
				eventsThisWeek.push_back(*iter);
		}
	}

	return eventsThisWeek;
}

vector<Item*> ItemBank::getAllEvents() {
	vector<Item*>events;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->isEvent()) {
			events.push_back(*iter);
		}
	}

	return events;
}

vector<Item*> ItemBank::getDeadlinesThisWeek() {
	vector<Item*> allDeadlines;
	vector<Item*> deadlinesThisWeek;
	
	allDeadlines = getAllDeadlines();

	for (vector<Item*>::iterator iter = allDeadlines.begin(); iter != allDeadlines.end(); iter++) {
		if (isThisWeekInPeriod((*iter)->getStartDateTime(), (*iter)->getEndDateTime())) {
				deadlinesThisWeek.push_back(*iter);
		}
	}

	return deadlinesThisWeek;
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




