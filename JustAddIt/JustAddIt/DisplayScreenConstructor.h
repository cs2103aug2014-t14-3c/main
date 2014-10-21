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

	vector<string> constructHomeScreen(vector<Item*>tasksToBeDisplayed, vector<Item*>deadlinesToBeDisplayed, vector<Item*>eventsToBeDisplayed);
	vector<string> constructEditScreen(Item* item);
	vector<string> constructSearchScreen(vector<Item*>tasksToBeDisplayed, vector<Item*>deadlinesToBeDisplayed, vector<Item*>eventsToBeDisplayed);
	vector<string> constructListScreen(vector<Item*>tasksToBeDisplayed, vector<Item*>deadlinesToBeDisplayed, vector<Item*>eventsToBeDisplayed);
	vector<string> constructCalendarScreen(vector<Item*>itemsToBeDisplayed);
	vector<string> constructOverdueScreen(vector<Item*>itemsToBeDisplayed);
	vector<string> clearScreen();
};