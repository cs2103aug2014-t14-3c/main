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

	vector<string> constructHomeScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events);
	vector<string> constructEditScreen(Item* item);
	vector<string> constructSearchScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events);
	vector<string> constructListScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events);
	vector<string> constructOverdueScreen(vector<Item*>items);
	vector<string> clearScreen();
};