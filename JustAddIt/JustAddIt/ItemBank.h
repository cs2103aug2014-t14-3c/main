#pragma once
#include "Item.h"

class ItemBank
{
private: 
	static vector<Item*> bank;
	static vector<Item*> initialBank;

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
	static void editItemPriorityInBank(vector<Item*>::iterator itemPtr, Item::PriorityLevel newPriority);

	static vector<Item*>::iterator findItemById(int id);
	static Item findItemByVectorPos(int i);

	static int getBankSize();
	static void initialiseBank();
	static void resetBank();
};

