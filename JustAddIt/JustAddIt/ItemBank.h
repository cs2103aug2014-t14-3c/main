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
	
	static void editItemTitleInBank(Item* item, string newTitle);
	static void editItemDescriptionInBank(Item* item, string newDescription);
	static void editItemStartDateTimeInBank(Item* item, tm newStartDateTime);
	static void editItemEndDateTimeInBank(Item* item, tm newEndDateTime);
	static void editItemVenueInBank(Item* item, string newVenue);
	static void editItemCategoryInBank(Item* item, string newCategory);
	static void editItemPriorityInBank(Item* item, string newPriority);

	static vector<Item*> getEvents();
	static vector<Item*> getDeadlines();
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
	static int getNumberOfMarkedItems();
	static void initialiseBank();
	static void deletePastEvents();
	static void resetBank();
};

