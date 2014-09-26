#pragma once
#include "Item.h"

using namespace std;

class CommandLogic
{
protected:
	static vector<Item> masterList;

	//sorts
	vector<string> sortAlphaAscending();
	vector<string> sortAlphaDescending();
	vector<string> sortDateAscending();
	vector<string> sortDateDescending();
	vector<string> sortPriority();

	//searches

public:
	virtual vector<string> execute();

};

