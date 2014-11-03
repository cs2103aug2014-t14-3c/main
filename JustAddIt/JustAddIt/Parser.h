#pragma once

#include "stdafx.h"

#include "Command.h"
#include "CmdAddItem.h"
#include "CmdSearch.h"
#include "CmdEditItem.h"
#include "CmdDeleteItem.h"
#include "CmdUndo.h"
#include "CmdMarkItemDone.h"
#include "CmdGoToListView.h"
#include "CmdHome.h"
#include "CmdShowOverdueDeadlines.h"
#include "CmdRedo.h"
#include "CmdClearAllDone.h"
#include "CmdClearAllOverdue.h"
#include "CmdExport.h"
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
	void detectTypesOfDatesAndEmbed(Item &myNewItem, string newFieldInfo, bool isDeadline);
	void detectCategoryAndEmbed(Item* myItem, string &stringDetails);
	void detectPriorityAndEmbed(Item* myItem, string &stringDetails);
	void detectDescriptionAndEmbed(Item* myItem, string &stringDetails);
	static bool isInteger(string query);
	static bool isMonth(string query);
	static bool isTime(string query);
	static bool isDayOfWeek(string query);
	int convertStringToIntHour(string stringTime);
	int convertStringToIntMin(string stringTime);
	static int convertStrToIntMonth(string month);
	static int convertDayOfWeekToIntDaysToAdd(string query, bool isNextWeek);
	
	static void convertStringToLowercase(string &myString);


	static bool isKeyword(string myWord);
	static bool isKeywordTime(string myWord);
	static bool isKeywordStartTime(string myWord);
	static bool isKeywordEndTime(string myWord);
	static bool isKeywordDeadline(string myWord);
	static bool isKeywordDate(string myWord);
	static bool isKeywordEndOfTitle(string myWord);
	vector <Item*> convertItemNumsToItemPtrs(string itemNumsStr);
	vector <string> convertStringToVector(string inputString);
	string convertVectorToString(vector<string>::iterator start, vector<string>::iterator end);
	
public:

	Command* stringToCommand(string userCommand);
	Parser(void);
	~Parser(void);


};

