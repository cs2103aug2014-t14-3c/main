#pragma once
#include "stdafx.h"
#include "Command.h"



class OutputControl {
public:
	enum CurrentScreenType { 
		HOME_SCREEN, 
		EDIT_SCREEN, 
		SEARCH_RESULTS_SCREEN, 
		TO_DO_LIST_VIEW, 
		CALENDAR_VIEW, 
		OVERDUE_TASKS_SCREEN 
	};

private:
	static vector<Item*> currentDisplayedItemList;
	static CurrentScreenType currentScreen;

//	static vector<string> addItemToVector(vector<string> targetVector, Item* item);

public:
	static void resetCurrentItemList();
	static void addItemToDisplayList(Item* itemPtr);
	static void setCurrentScreen(CurrentScreenType newScreen);

	static Item* getItemAddr(int itemLocationInList);
//	static vector<string> constructOutput(CurrentScreenType newScreen);
};
