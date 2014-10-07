#pragma once
#include "stdafx.h"
#include "Command.h"

class OutputControl {
public:
	enum CurrentScreenType { 
		HOME_SCREEN, 
		EDIT_SCREEN, 
		DELETE_SCREEN,
		SEARCH_RESULTS_SCREEN, 
		TO_DO_LIST_VIEW, 
		CALENDAR_VIEW, 
		OVERDUE_TASKS_SCREEN 
	};

private:
	static vector<Item*> currentDisplayedItemList;
	static CurrentScreenType currentScreen;

public:
	static void resetCurrentItemList();
	static void addItemToDisplayList(Item* itemPtr);
	static void setCurrentScreen(CurrentScreenType newScreen);

	static Item* getItemAddr(int itemLocationInList);

};
