//@author A0116781A
#include "stdafx.h"
#include "ItemBank.h"

#define SEVEN_DAYS_IN_SECONDS 604800

ItemBank* ItemBank::itemBank = NULL;
bool ItemBank::instanceFlag = false;

vector<Item*> ItemBank::initialBank;
vector<Item*> ItemBank::bank;

const string ItemBank::MESSAGE_INVALID_ITEM = "item does not exist!";

ItemBank::ItemBank() {

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

void ItemBank::initialiseBank() {
	DataStorage* dataStorage = dataStorage->getInstance();

	strToBank(dataStorage->readFromLocalMemory());

	return;
}

void ItemBank::strToBank(vector<string> items) {
	vector<string>::iterator iter = items.begin();

	bank.clear();
	initialBank.clear();

	while (iter != items.end()) {
		Item* newItem = new Item;

		iter = newItem->strToItem(iter);

		bank.push_back(newItem);
		copyItemToInitialBank(newItem);
	}
}

void ItemBank::resetBank() {
	bank.clear();
	for(vector<Item*>::iterator iter = initialBank.begin(); iter != initialBank.end(); iter++) {
		Item* itemPtr = new Item;
		*itemPtr = **iter;
		addToBank(itemPtr);
	}
}

void ItemBank::clearBank() {
	bank.clear();
	update();
}

bool ItemBank::addToBank(Item* itemPtr) {
	//if(bank.empty()) {
		bank.push_back(itemPtr);
	//} else {
	//	vector<Item*>::iterator iter = findLocationToInsert(itemPtr);
	//	bank.insert(iter, itemPtr);
	//}

	update();

	return checkForConflict(itemPtr);
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

void ItemBank::deleteItems(vector<Item*> itemsToDelete) {
	for(vector<Item*>::iterator iter = itemsToDelete.begin(); iter != itemsToDelete.end(); iter++) {
		deleteItem(*iter);
	}
	update();
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

void ItemBank::editItemPriority(Item* item, Item::PriorityLevel newPriority) {
	vector<Item*>::iterator itemIter = findIter(item);
	(*itemIter)->setPriority(newPriority);
	update();
}

vector<Item*> ItemBank::getPastEvents() {
	vector<Item*> allEvents;
	vector<Item*> pastEvents; 

	allEvents = getAllEvents();

	for(vector<Item*>::iterator iter = allEvents.begin(); iter != allEvents.end(); iter++) {
		if(isEventPast(*iter)) {
			pastEvents.push_back(*iter);
		}
	}

	return pastEvents;
}

vector<Item*> ItemBank::getOverdueDeadlines() {
	vector<Item*> allDeadlines;
	vector<Item*> overdueDeadlines;

	allDeadlines = getAllDeadlines();
	
	for (vector<Item*>::iterator iter = allDeadlines.begin(); iter != allDeadlines.end(); iter++) {
		if (isOverdue(*iter)) {
			overdueDeadlines.push_back(*iter);
		}
	}

	return overdueDeadlines;
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

int ItemBank::getNumberOfMarkedItems() {
	vector<Item*> markedDone = getDoneItems();

	return (int)markedDone.size();
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

vector<Item*> ItemBank::getAllEvents() {
	vector<Item*>events;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		if ((*iter)->isEvent()) {
			events.push_back(*iter);
		}
	}

	return events;
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

void ItemBank::update() {
	vector<string>items;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		items = updateItem(items, *iter);
	}
	
	DataStorage* dataStorage = dataStorage->getInstance();
	dataStorage->writeToFile(items);

	return;
}

bool ItemBank::checkForConflict(Item* itemPtr) {
	vector<Item*> allEvents;
	vector<Item*> conflictedEvents;

	allEvents = getAllEvents();

	for (vector<Item*>::iterator iter = allEvents.begin(); iter != allEvents.end(); iter++) {
		if (*iter != itemPtr && isConflicted(itemPtr, *iter)) {
			conflictedEvents.push_back(*iter);
		}
	}

	return !conflictedEvents.empty();
}

bool ItemBank::isConflicted(Item* itemPtr1, Item* itemPtr2) {
	time_t item1Start = itemPtr1->getStartDateTime_T();
	time_t item1End = itemPtr1->getEndDateTime_T();
	time_t item2Start = itemPtr2->getStartDateTime_T();
	time_t item2End = itemPtr2->getEndDateTime_T();

	if(item1Start >= item2End || 
		item1End <= item2Start) {
		return false;
	}

	return true;
}

//unused as could not debug in time.
//vector<Item*>::iterator ItemBank::findLocationToInsert(Item* itemPtr) {
//
//	if(itemPtr->getItemType() == Item::ItemType::TASK) {
//		return bank.end();
//	} else if(itemPtr->getItemType() == Item::ItemType::DEADLINE) {
//		return findLocationInDeadlines(itemPtr);
//	} else if(itemPtr->getItemType() == Item::ItemType::EVENT) {
//		return findLocationInEvents(itemPtr);
//	}
//		//} else if((*iter)->getItemType() == Item::ItemType::DEADLINE) {
//		//	if(isTimePast(itemPtr->getStartDateTime_T(), (*iter)->getEndDateTime_T())) {
//		//		if(iter == bank.begin()) {
//		//			return iter;
//		//		} else if(++iter == bank.end()) {
//		//			return iter;
//		//		}
//		//	}
//		//}
//}
//
//vector<Item*>::iterator ItemBank::findLocationInDeadlines(Item* itemPtr) {
//	vector<Item*>::iterator iter = getAllDeadlines().begin();
//
//	while((*iter)->getItemType() != Item::ItemType::TASK &&
//		isTimePast(itemPtr->getEndDateTime_T(), (*iter)->getEndDateTime_T())) {
//			if(iter == getAllDeadlines().begin()) {
//				return findIter(*iter);
//			} else if(++iter == getAllDeadlines().end()) {
//				return bank.end();
//			} else {
//				iter++;
//			}
//	}
//	return bank.end();
//}
//
//vector<Item*>::iterator ItemBank::findLocationInEvents(Item* itemPtr) {
//	vector<Item*> allEvents = getAllEvents();
//	vector<Item*>::iterator iter = allEvents.begin();
//
//	assert(allEvents.begin() != allEvents.end());
//
//	while(iter != allEvents.end()) {
//		if(isTimePast(itemPtr->getStartDateTime_T(), (*iter)->getStartDateTime_T()) ||
//			isTimePast(itemPtr->getEndDateTime_T(), (*iter)->getEndDateTime_T())) {
//				if(iter == allEvents.begin()) {
//					return findIter(*iter);
//				} else if(++iter == allEvents.end()) {
//					return bank.end();
//				}
//				iter--;
//		} else if(isTimePast((*iter)->getStartDateTime_T(), itemPtr->getStartDateTime_T()) ||
//			isTimePast((*iter)->getEndDateTime_T(), itemPtr->getEndDateTime_T())) {
//				if(iter == allEvents.begin()) {
//					return findIter(*iter);
//				} else if(++iter == allEvents.end()) {
//					return bank.end();
//				}
//				iter--;
//		} 
//		iter++;
//	}
//
//	return bank.end();
//}

bool ItemBank::isEventPast(Item* itemPtr) {
	return itemPtr->isEvent() && isTimePast(itemPtr->getEndDateTime());
}

bool ItemBank::isOverdue(Item* itemPtr) {
	return itemPtr->isDeadline() && isTimePast(itemPtr->getEndDateTime());
}

void ItemBank::toggleItemDone(Item* itemPtr) {
	vector<Item*>::iterator itemIter = findIter(itemPtr);
	(*itemIter)->toggleDone();
}

void ItemBank::deleteItem(Item* itemPtr) {
	bank.erase(findIter(itemPtr));
}

void ItemBank::copyItemToInitialBank(Item* itemPtr) {
	Item* newItem = new Item;
	*newItem = *itemPtr;
	initialBank.push_back(newItem);
}

vector<Item*>::iterator ItemBank::findIter(Item* itemPtr) {
	vector<Item*>::iterator iter = bank.begin();

	while(iter != bank.end()) {
		if((*iter)->getId() == itemPtr->getId()) {
			return iter;
		}
		iter++;
	}

	throw logic_error(MESSAGE_INVALID_ITEM);
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

bool ItemBank::searchKeyword(string itemAttribute, string keyword) {
	size_t wordPosition = itemAttribute.find(keyword);

	if (wordPosition != string::npos) {
		return true;
	}

	return false;
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

bool ItemBank::isDateThisWeek(tm timeInTm) {
	time_t currentTime;
	std::time(&currentTime);
	time_t oneWeekLaterTime = currentTime + SEVEN_DAYS_IN_SECONDS;
	time_t givenTime = mktime(&timeInTm);


	return givenTime <= oneWeekLaterTime && givenTime >= currentTime;
}

bool ItemBank::isDateAfterThisWeek(tm timeInTm) {
	time_t oneWeekLaterTime;
	std::time(&oneWeekLaterTime);
	oneWeekLaterTime += SEVEN_DAYS_IN_SECONDS;
	time_t givenTime = mktime(&timeInTm);


	return givenTime >= oneWeekLaterTime;
}

//checks if comp (comparator) occurs before ref (reference)
bool ItemBank::isTimePast(time_t comp, time_t ref) {
	return comp < ref;
}

bool ItemBank::isTimePast(tm time) {
	time_t currentTime;
	std::time(&currentTime);

	return mktime(&time) <= currentTime;
}

int ItemBank::getBankSize() {
	return (int)bank.size();
}