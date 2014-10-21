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
	static void addToBank(Item* item);
	static void deleteFromBank(vector<Item*>::iterator itemPtr);
	static void markItemInBank(vector<Item*>::iterator itemPtr);
	static void editItemTitleInBank(vector<Item*>::iterator itemPtr, string newTitle);
	static void editItemDescriptionInBank(vector<Item*>::iterator itemPtr, string newDescription);
	static void editItemStartDateTimeInBank(vector<Item*>::iterator itemPtr, struct tm newStartDateTime);
	static void editItemEndDateTimeInBank(vector<Item*>::iterator itemPtr, struct tm newEndDateTime);
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

	static vector<Item*>::iterator findItemById(int id);
	static Item findItemByVectorPos(int i);

	static int getBankSize();
	static void initialiseBank();
	static void resetBank();
};

