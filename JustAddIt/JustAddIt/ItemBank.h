#pragma once
#include "Item.h"

class ItemBank
{
private: 
	static vector<Item> bank;
	static vector<Item> initialBank;

public:
	static void addToBank(Item item);
	static void deleteFromBank(vector<Item>::iterator itemPtr);
	static void markItemInBank(vector<Item>::iterator itemPtr);

	static vector<Item>::iterator findItemById(int id);
	static Item findItemByVectorPos(int i);

	static int getBankSize();
	static void initialiseBank();
	static void resetBank();
};

