#pragma once
#include "Item.h"

using namespace std;

class CommandLogic
{
private:

public:
	
	static vector<Item> masterList;
	static vector<Item> displayOrder;

	virtual vector<string> execute();
	
	//sorts
	vector<string> sortAlphaAscending();
	vector<string> sortAlphaDescending();
	vector<string> sortDateAscending();
	vector<string> sortDateDescending();
	vector<string> sortPriority();
};

