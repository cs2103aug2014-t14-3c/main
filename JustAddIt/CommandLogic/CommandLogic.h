#pragma once
#include "DataStorage.h"

using namespace std;

class CommandLogic
{
protected:
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

