#pragma once
#include "Command.h"
#include "Item.h"

class DisplayScreenConstructor
{
private:
	static DisplayScreenConstructor* displayScreenConstructor;
	vector<string>outputMessageStorage;

	DisplayScreenConstructor(void);

public:
	static DisplayScreenConstructor* getInstance(void);
	~DisplayScreenConstructor(void);

	vector<string> constructHomeScreen();
	vector<string> constructEditScreen(Item* item);
	vector<string> constructSearchScreen(vector<Item*>itemsToBeDisplayed);
	vector<string> constructListScreen_1Week(vector<Item*>itemsToBeDisplayed);
	vector<string> constructListScreen_2Weeks(vector<Item*>itemsToBeDisplayed);
	vector<string> constructListScreen_3Weeks(vector<Item*>itemsToBeDisplayed);
	vector<string> constructListScreen_Month(vector<Item*>itemsToBeDisplayed);
	vector<string> constructCalendarScreen(vector<Item*>itemsToBeDisplayed);
	vector<string> constructOverdueScreen(vector<Item*>itemsToBeDisplayed);
	vector<string> clearScreen();
};