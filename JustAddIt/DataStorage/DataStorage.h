#pragma once
#include "Item.h"

using namespace std;

class DataStorage
{
private:
	static vector<Item> masterList;

	void writeToTxtFile();

public:
	void initialiseStorage();
	void addToList();
	void deleteFromList();
	vector<Item>::iterator getItem(int position); //TODO: getItem via item id 

};