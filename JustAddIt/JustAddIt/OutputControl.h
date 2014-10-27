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
	static CurrentScreenType currentBaseScreen;

public:
	static void resetCurrentItemList();
	static void addItemToDisplayList(Item* itemPtr);
	static void setCurrentScreen(CurrentScreenType newScreen);
	static void setCurrentBaseScreen(CurrentScreenType newScreen);
	static void setCurrentDisplayedItemList(vector<Item*> newList);
	static int getNumberOfDisplayedItems();
	static Item* getItemAddr(int itemLocationInList);
	static vector<Item*>::iterator getCurrentDisplayedItemList();
	static CurrentScreenType getCurrentScreen();
	static CurrentScreenType getCurrentBaseScreen();



};


