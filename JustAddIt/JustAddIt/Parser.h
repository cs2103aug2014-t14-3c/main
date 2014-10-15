#pragma once
#include <iostream>
#include "stdafx.h"
#include <time.h>
#include <ctype.h>
#include <sstream>
#include <iterator>
#include "Command.h"
#include "CmdAddItem.h"
#include "CmdSearch.h"
#include "CmdEditItem.h"
#include "CmdDeleteItem.h"
#include "CmdUndo.h"
#include "CmdMarkItemDone.h"
#include "CmdGoToCalendarView.h"
#include "CmdGoToListView.h"
#include "CmdShowOverdueTasks.h"


enum CommandType {
	ADD, SEARCH, EDIT, DELETE, MARK, SAVE, CANCEL, UNDO, VIEW_CALENDAR, VIEW_TODOLIST, VIEW_OVERDUE
};

class Parser
{
public:
	void embedDetailsInItem(Item* myItem, string stringDetails);
	void detectTitleAndEmbed(Item* myItem, string &stringDetails);
	bool detectDeadlineKeywordAndTrim(string &stringDetails);
	bool detectTimeAndEmbedIsOk(Item* myItem, string stringDetails, bool isDeadline);
	bool detectMonthDateAndEmbedIsOk(Item* myItem, string &stringDetails, bool isDeadline);
	bool detectDayOfWeekDateAndEmbedIsOk(Item* myItem, string &stringDetails, bool isDeadline);
	bool isInteger(string query);
	bool isMonth(string query);
	bool isTime(string query);
	bool isDayOfWeek(string query);
	int convertStringToIntHour(string stringTime);
	int convertStringToIntMin(string stringTime);
	int convertStrToIntMonth(string month);
	int convertDayOfWeekToIntDaysToAdd(string query);
	
	void convertStringToLowercase(string &myString);
	CommandType determineCommandType(string userCommand, OutputControl::CurrentScreenType currentScreen);
	CommandType determineCommandType_HomeScreen(string userCommand);
	CommandType determineCommandType_EditScreen(string userCommand);
	CommandType determineCommandType_DeleteScreen(string userCommand);
	CommandType determineCommandType_SearchResultsScreen(string userCommand);
	CommandType determineCommandType_ToDoListView(string userCommand);
	CommandType determineCommandType_CalendarView(string userCommand);
	CommandType determineCommandType_OverdueTasksScreen(string userCommand);

	bool isKeyword(string myWord);
	bool isKeywordTime(string myWord);
	bool isKeywordStartTime(string myWord);
	bool isKeywordEndTime(string myWord);
	bool isKeywordDate(string myWord);
public:
	Command* stringToCommand(string userCommand);
	Parser(void);
	~Parser(void);
};

