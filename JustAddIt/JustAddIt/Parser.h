#pragma once

#include "stdafx.h"

#include "Command.h"
#include "CmdAddItem.h"
#include "CmdSearch.h"
#include "CmdEditItem.h"
#include "CmdDeleteItem.h"
#include "CmdUndo.h"
#include "CmdMarkItemDone.h"
#include "CmdGoToCalendarView.h"
#include "CmdGoToListView.h"
#include "CmdHome.h"
#include "CmdShowOverdueDeadlines.h"
#include "CmdRedo.h"
#include "ParserForCmds.h"
#include "Item.h"




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
	int convertDayOfWeekToIntDaysToAdd(string query, bool isNextWeek);
	
	void convertStringToLowercase(string &myString);


	bool isKeyword(string myWord);
	bool isKeywordTime(string myWord);
	bool isKeywordStartTime(string myWord);
	bool isKeywordEndTime(string myWord);
	bool isKeywordDate(string myWord);
	vector <Item*> convertFieldNumsToItemPtrs(string fieldNumsStr);
public:

	Command* stringToCommand(string userCommand);
	Parser(void);
	~Parser(void);


};

