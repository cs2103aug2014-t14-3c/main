#pragma once
#include "stdafx.h"
#include "Command.h"

#define MAX_SIZE 100

class OutputConstructor {
private:
	static string dateToString(tm* date);

public:
	enum CurrentScreenType { HOME_SCREEN, EDIT_SCREEN, SEARCH_RESULTS_SCREEN, TO_DO_LIST_VIEW, CALENDAR_VIEW, OVERDUE_TASKS_SCREEN };

	static vector<Item*> currentDisplayedItemList;
	static CurrentScreenType currentScreen;

	static vector<string> constructOutput(CurrentScreenType newScreen);

	static void resetCurrentItemList();
	static void addItemToDisplayList(Item* itemPtr);

	static vector<string> addItemToVector(vector<string> targetVector, Item* item);
	static string OutputConstructor::priorityToString(Item::PriorityLevel priority); 
};
