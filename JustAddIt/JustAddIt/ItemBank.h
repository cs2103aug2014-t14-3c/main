#pragma once
#include "Item.h"
#include "DataStorage.h"


class ItemBank
{
private: 
	static vector<Item*> initialBank;
	static vector<Item*> bank;

	static void update();
	static bool checkForConflict(Item* itemPtr);
	static bool searchKeyword(string itemAttribute, string keyword);

	static bool isEventPast(Item* itemPtr);
	static bool isOverdue(Item* itemPtr);
	static bool isTimePast(tm time);
	static void toggleItemDone(Item* itemPtr);
	static void deleteItem(Item* itemPtr);
	static vector<Item*> getDoneItems();

	static bool isHighPriority(string priority);
	static bool isMedPriority(string priority);
	static bool isLowPriority(string priority);

public:

	
	static void deleteItems(vector<Item*> itemPtr);
	static void deleteDoneItems();
	static void deleteOverdueDeadlines();
	static void deletePastEvents();	

	static void toggleItemsDone(vector<Item*> itemPtrs);

	
	static void editItemTitle(Item* item, string newTitle);
	static void editItemDescription(Item* item, string newDescription);
	static void editItemStartDateTime(Item* item, tm newStartDateTime);
	static void editItemEndDateTime(Item* item, tm newEndDateTime);
	static void editItemVenue(Item* item, string newVenue);
	static void editItemCategory(Item* item, string newCategory);
	static void editItemPriority(Item* item, string newPriority);

	static bool isFoundForSearchingEvents(string keyword);
	static bool isFoundForSearchingDeadlines(string keyword);
	static bool isFoundForSearchingTasks(string keyword);
	
	static vector<Item*> searchEvents(string keyword);
	static vector<Item*> searchDeadlines(string keyword);
	static vector<Item*> searchTasks(string keyword);
	
	static vector<Item*>::iterator findIter(Item* itemPtr);

	static vector<Item*> getAllTasks();
	static vector<Item*> getEventsThisWeek();
	static vector<Item*> getAllEvents();
	static vector<Item*> getPastEvents();
	static vector<Item*> getDeadlinesThisWeek();
	static vector<Item*> getAllDeadlines(); 
	static vector<Item*> getOverdueDeadlines();

	static int getBankSize();
	//static int getNumberOfMarkedItems();

	static void initialiseBank();
	static void resetBank();
	static bool addToBank(Item* item);
};

