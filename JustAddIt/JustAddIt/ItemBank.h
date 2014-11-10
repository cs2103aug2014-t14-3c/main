//@author A0116781A
//
//-----------------------------------------------
//This is the ItemBank class. It is responsible 
//for storing all the items in JustAddIt.
//
//Whenever a command that creates, modifies or 
//deletes an item, the appropriate item is found/
//created and the respective method called by the
//command will act on it.
//
//ItemBank will edit, create, delete and filter 
//the items based on item type, whether it is 
//overdue, et cetera.  
// 
//On initialisation, ItemBank will translate a 
//strings taken from DataStorage into items and
//load it into the bank. A backup copy is kept 
//to support undo capability.
//
//-----------------------------------------------

#pragma once
#include "Item.h"
#include "DataStorage.h"


class ItemBank
{
private: 
	static bool instanceFlag;
	static ItemBank* itemBank;
	
	ItemBank();

	static vector<Item*> initialBank;
	static vector<Item*> bank;

	static const string MESSAGE_INVALID_ITEM;

	void deleteItem(Item* itemPtr);

	vector<Item*> getDoneItems();

	bool isTimePast(tm time);
	bool isTimePast(time_t comp, time_t ref);
	bool isDateThisWeek(tm time);
	bool isDateAfterThisWeek(tm timeInTm);
	bool isThisWeekInPeriod(tm timeStart, tm timeEnd);
	bool isEventPast(Item* itemPtr);
	bool isOverdue(Item* itemPtr);

	//vector<Item*>::iterator findLocationToInsert(Item* itemPtr);
	//vector<Item*>::iterator findLocationInEvents(Item* itemPtr);
	//vector<Item*>::iterator findLocationInDeadlines(Item* itemPtr);

	void strToBank(vector<string> items);
	void copyItemToInitialBank(Item* itemPtr);

	void setItemType(vector<string> items, Item* item);
	void setDone(vector<string> items, Item* item);
	void setCategory(vector<string> items, Item* item);

	void toggleItemDone(Item* itemPtr);	

	void update();
	vector<string> updateItem(vector<string> items, Item* item);

public:
	~ItemBank();
	static ItemBank* getInstance();

	bool addToBank(Item* itemPtr);
	void initialiseBank();
	void clearBank();
	void resetBank();

	bool checkForConflict(Item* itemPtr);
	bool isConflicted(Item* item1, Item* item2);

	void deleteItems(vector<Item*> itemPtr);
	void deleteDoneItems();
	void deleteOverdueDeadlines();
	void deletePastEvents();

	void editItemTitle(Item* item, string newTitle);
	void editItemDescription(Item* item, string newDescription);
	void editItemStartDateTime(Item* item, tm newStartDateTime);
	void editItemEndDateTime(Item* item, tm newEndDateTime);
	void editItemVenue(Item* item, string newVenue);
	void editItemCategory(Item* item, string newCategory);
	void editItemPriority(Item* item, Item::PriorityLevel newPriority);
	
	vector<Item*>::iterator findIter(Item* itemPtr);

	vector<Item*> getAllTasks();
	vector<Item*> getEventsThisWeek();
	vector<Item*> getAllEvents();
	vector<Item*> getPastEvents();
	vector<Item*> getDeadlinesThisWeek();
	vector<Item*> getAllDeadlines(); 
	vector<Item*> getOverdueDeadlines();

	int getBankSize();
	int getNumberOfMarkedItems();

	bool isFoundForSearchingEvents(string keyword);
	bool isFoundForSearchingDeadlines(string keyword);
	bool isFoundForSearchingTasks(string keyword);

	void toggleItemsDone(vector<Item*> itemPtrs);

	bool searchKeyword(string itemAttribute, string keyword);

	vector<Item*> searchEvents(string keyword);
	vector<Item*> searchDeadlines(string keyword);
	vector<Item*> searchTasks(string keyword);

};

