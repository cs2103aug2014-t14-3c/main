#pragma once

#include "stdafx.h"
#include "ItemBank.h"
#include "OutputControl.h"

#define MAX_SIZE 100

using namespace std;

class Command
{
protected:
	static const string FORMAT_TITLE;
	static const string FORMAT_DESCRIPTION;
	static const string FORMAT_START;
	static const string FORMAT_END;
	static const string FORMAT_VENUE;
	static const string FORMAT_PRIORITY;
	static const string FORMAT_CATEGORY;	
	static const string FORMAT_DIVIDER; 

	vector<string> outputMessageStorage;

	virtual vector<string> itemToString(Item* itemPtr);

	virtual vector<string> constructOutput();

public:
	Command(void);
	~Command(void);
	virtual vector<string> execute();

};