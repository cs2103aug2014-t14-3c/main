//@author A0116781A
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

	bool checkForConflict(Item* itemPtr);

	void deleteItem(Item* itemPtr);

	vector<Item*> getDoneItems();

	bool isTimePast(tm time);
	bool isDateThisWeek(tm time);
	bool isDateAfterThisWeek(tm timeInTm);
	bool isThisWeekInPeriod(tm timeStart, tm timeEnd);
	bool isEventPast(Item* itemPtr);
	bool isOverdue(Item* itemPtr);

	bool isHighPriority(string priority);
	bool isMedPriority(string priority);
	bool isLowPriority(string priority);

	void setItemType(vector<string> items, Item* item);
	void setDone(vector<string> items, Item* item);
	void setCategory(vector<string> items, Item* item);

	void toggleItemDone(Item* itemPtr);	

	void update();
	vector<string> updateItem(vector<string> items, Item* item);

public:
	~ItemBank();
	static ItemBank* getInstance();

	bool addToBank(Item* item);
	void initialiseBank();
	void clearBank();
	void resetBank();

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

