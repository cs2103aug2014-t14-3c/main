#pragma once
#include "Item.h"

class ItemBank
{
private: 
	static vector<Item> bank;

public:
	static void addToBank(Item item);
	static void removeFromBank(vector<Item>::iterator itemPtr);

	static vector<Item>::iterator findItemById(int id);
};

