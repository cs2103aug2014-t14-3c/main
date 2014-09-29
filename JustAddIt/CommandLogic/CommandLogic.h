#pragma once
#include "DataStorage.h"

using namespace std;

class CommandLogic
{
protected:
	//static vector<string> outputMessageStorage;

	//sorts
	vector<string> sortAlphaAscending();
	vector<string> sortAlphaDescending();
	vector<string> sortDateAscending();
	vector<string> sortDateDescending();
	vector<string> sortPriority();

	//searches

public:
	static vector<string> outputMessageStorage;

	virtual vector<string> execute();

};

