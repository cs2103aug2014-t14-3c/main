#pragma once
#include "Item.h"
#include "DataStorage.h"


class ItemBank
{
private: 
	static vector<Item*> initialBank;
	static vector<Item*> bank;
	static void update();

public:
	static bool addToBank(Item* item);
	static bool checkForConflict(Item* item);
	static void deleteFromBank(vector<Item*> itemPtr);
	static void deleteAllDoneItemsFromBank();
	static void deleteAllOverdueDeadlinesFromBank();
	static void markItemsInBank(vector<Item*> itemPtr);
	static void editItemTitleInBank(vector<Item*>::iterator itemPtr, string newTitle);
	static void editItemDescriptionInBank(vector<Item*>::iterator itemPtr, string newDescription);
	static void editItemStartDateTimeInBank(vector<Item*>::iterator itemPtr, tm newStartDateTime);
	static void editItemEndDateTimeInBank(vector<Item*>::iterator itemPtr, tm newEndDateTime);
	static void editItemVenueInBank(vector<Item*>::iterator itemPtr, string newVenue);
	static void editItemCategoryInBank(vector<Item*>::iterator itemPtr, string newCategory);
	static void editItemPriorityInBank(vector<Item*>::iterator itemPtr, string newPriority);
	static vector<Item*> getEvents(struct tm cutOffDateTime);
	static vector<Item*> getDeadlines(struct tm cutOffDateTime);
	static vector<Item*> getAllEvents();
	static vector<Item*> getAllDeadlines(); 
	static vector<Item*> getTasks();
	static vector<Item*> getOverdueDeadlines();
	static bool searchKeywordInItemAttribute(string itemAttribute, string keyword);
	static vector<Item*> searchEvents(string keyword);
	static vector<Item*> searchDeadlines(string keyword);
	static vector<Item*> searchTasks(string keyword);
	static vector<Item*>::iterator findIter(Item* itemPtr);

	static vector<Item*>::iterator findItemById(int id);
	static Item findItemByVectorPos(int i);

	static int getBankSize();
	static void initialiseBank();
	static void deletePastEvents();
	static void resetBank();
};

