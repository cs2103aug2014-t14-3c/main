//@author A0108397W
#pragma once
#include "Item.h"
#include "Exporter.h"

class DisplayScreenConstructor
{
private:
	static const string TEMPLATE_SCREEN_HOME;
	static const string TEMPLATE_SCREEN_EDIT;
	static const string TEMPLATE_SCREEN_SEARCH; 
	static const string TEMPLATE_SCREEN_LISTVIEW;
	static const string TEMPLATE_SCREEN_OVERDUE; 
	static const string HOME_WEEK_CLEAR;
	static const string HOME_HAPPENINGS;
	static const string EDIT_HEADER;
	static const string EDIT_TITLE_FIELD;
	static const string EDIT_DESCRIPTION_FIELD;
	static const string EDIT_START_TIME_FIELD;
	static const string EDIT_END_TIME_FIELD;
	static const string EDIT_PRIORITY_FIELD;
	static const string EDIT_CATEGORY_FIELD;
	static const string SEARCH_SHOW_RESULTS;
	static const string SEARCH_NO_RESULTS;
	static const string LISTVIEW_ALL_EVENTS;
	static const string LISTVIEW_NO_EVENTS;
	static const string LISTVIEW_NO_DEADLINES; 
	static const string LISTVIEW_NO_TASKS;
	static const string OVERDUE_HEADER;
	static const string OVERDUE_NO_OVERDUE;
	static const string OVERDUE_DUE;
	static const string PERIOD;
	static const string FROM;
	static const string TO;
	static const string BY;
	static const string DEFAULT_INPUT;
	static const string BLANK;
	static const string NEW_LINE;
	static const string MARK_DONE;

	static DisplayScreenConstructor* displayScreenConstructor;
	vector<string>outputMessageStorage;

	DisplayScreenConstructor(void);
	vector<string> displayItemsOnHomeScreen(vector<Item*> tasks, vector<Item*> deadlines, vector<Item*> events);
	vector<string> displayItemsOnSearchScreen(vector<Item*> tasks, vector<Item*> deadlines, vector<Item*> events, string keyword);
	vector<string> displayItemsOnListView(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events);
	vector<string> displayItemsOnOverdueScreen (vector<Item*>items);
	void exportToFile(vector<string>displayScreen);
	vector<string> constructEventList(vector<Item*> events, int &displayCounter);
	vector<string> constructDeadlineList(vector<Item*> deadlines, int &displayCounter);
	vector<string> constructTaskList(vector<Item*> tasks, int &displayCounter);
	vector<string> constructOverdueList(vector<Item*>overdueItems, int &displayCounter);
	string constructEventDisplay(vector<Item*>::iterator iter, int displayCounter);
	string constructDeadlineDisplay(vector<Item*>::iterator iter, int displayCounter);
	string constructTaskDisplay(vector<Item*>::iterator iter, int displayCounter);
	string constructOverdueItemDisplay(vector<Item*>::iterator iter, int displayCounter);

public:
	static DisplayScreenConstructor* getInstance(void);
	~DisplayScreenConstructor(void);

	vector<string> constructHomeScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events);
	vector<string> constructEditScreen(Item* item);
	vector<string> constructSearchScreen(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events, string keyword);
	vector<string> constructListView(vector<Item*>tasks, vector<Item*>deadlines, vector<Item*>events);
	vector<string> constructOverdueScreen(vector<Item*>items);
	vector<string> clearScreen();
};