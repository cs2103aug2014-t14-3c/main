//@author A0110770U
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
	static string currentKeywordSearched;

public:
	static void resetCurrentItemList();
	static void addItemToDisplayList(Item* itemPtr);
	//setters
	static void setCurrentScreen(CurrentScreenType newScreen);
	static void setCurrentBaseScreen(CurrentScreenType newScreen);
	static void setCurrentDisplayedItemList(vector<Item*> newList);
	static void setCurrentKeywordSearched(string keyword);
	//getters
	static int getNumberOfDisplayedItems();
	static Item* getItemAddr(int itemLocationInList);
	static vector<Item*>::iterator getCurrentDisplayedItemList();
	static CurrentScreenType getCurrentScreen();
	static CurrentScreenType getCurrentBaseScreen();
	static string getCurrentKeywordSearched();



};


