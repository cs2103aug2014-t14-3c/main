//@author A0116781A
#pragma once
#include "Item.h"
#include "DataStorage.h"


class ItemBank
{
private: 
	static const int sevenDaysInSeconds;

	static vector<Item*> initialBank;
	static vector<Item*> bank;

	static bool checkForConflict(Item* itemPtr);

	static void deleteItem(Item* itemPtr);

	static vector<Item*> getDoneItems();

	static bool isTimePast(tm time);
	static bool isDateThisWeek(tm time);
	static bool isDateAfterThisWeek(tm timeInTm);
	static bool isThisWeekInPeriod(tm timeStart, tm timeEnd);
	static bool isEventPast(Item* itemPtr);
	static bool isOverdue(Item* itemPtr);

	static bool isHighPriority(string priority);
	static bool isMedPriority(string priority);
	static bool isLowPriority(string priority);

	static void setItemType(vector<string> items, Item* item);
	static void setDone(vector<string> items, Item* item);
	static void setCategory(vector<string> items, Item* item);

	static void toggleItemDone(Item* itemPtr);	

	static void update();
	static vector<string> updateItem(vector<string> items, Item* item);

public:

	static bool addToBank(Item* item);
	static void initialiseBank();
	static void clearBank();
	static void resetBank();

	static void deleteItems(vector<Item*> itemPtr);
	static void deleteDoneItems();
	static void deleteOverdueDeadlines();
	static void deletePastEvents();

	static void editItemTitle(Item* item, string newTitle);
	static void editItemDescription(Item* item, string newDescription);
	static void editItemStartDateTime(Item* item, tm newStartDateTime);
	static void editItemEndDateTime(Item* item, tm newEndDateTime);
	static void editItemVenue(Item* item, string newVenue);
	static void editItemCategory(Item* item, string newCategory);
	static void editItemPriority(Item* item, string newPriority);
	
	static vector<Item*>::iterator findIter(Item* itemPtr);

	static vector<Item*> getAllTasks();
	static vector<Item*> getEventsThisWeek();
	static vector<Item*> getAllEvents();
	static vector<Item*> getPastEvents();
	static vector<Item*> getDeadlinesThisWeek();
	static vector<Item*> getAllDeadlines(); 
	static vector<Item*> getOverdueDeadlines();

	static int getBankSize();
	static int getNumberOfMarkedItems();

	static bool isFoundForSearchingEvents(string keyword);
	static bool isFoundForSearchingDeadlines(string keyword);
	static bool isFoundForSearchingTasks(string keyword);

	static void toggleItemsDone(vector<Item*> itemPtrs);

	static bool searchKeyword(string itemAttribute, string keyword);

	static vector<Item*> searchEvents(string keyword);
	static vector<Item*> searchDeadlines(string keyword);
	static vector<Item*> searchTasks(string keyword);

};

