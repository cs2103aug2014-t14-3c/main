//@author A0108397W
#pragma once
#include "Item.h"
#include "Exporter.h"

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
	vector<string> constructOverdueScreen(vector<Item*>itemsToBeDisplayed);
	vector<string> clearScreen();
};