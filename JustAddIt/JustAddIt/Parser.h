#pragma once
//@author A0110770U
//
//------------------------------------------
//Parser acts as a translator from user
//input to Command objects. 
//
//New keywords can be updated by modifying the
//respective bool functions such as isMonth, 
//isKeywordTime, isHighPriority.
//
//If new fields are needed to be parsed
//follow a similar format to the detectAndEmbed
//functions that are available.
//
//Parser will throw exceptions if it detects
//any invalid command or invalid field input.
//------------------------------------------
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


//TODO: REMOVE THIS WHEN NOT IN UNIT TEST MODE
//#define TESTMODE
class Parser
{
#ifndef TESTMODE 
private: 
#else 
public: 
#endif
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
	static bool isKeyword(string myWord);
	static bool isKeywordTime(string myWord);
	static bool isKeywordStartTime(string myWord);
	static bool isKeywordEndTime(string myWord);
	static bool isKeywordDeadline(string myWord);
	static bool isKeywordDate(string myWord);
	static bool isKeywordEndOfTitle(string myWord);
	bool isHighPriority(string priority);
	bool isMedPriority(string priority);
	bool isLowPriority(string priority);
	
	int convertStringToIntHour(string stringTime);
	int convertStringToIntMin(string stringTime);
	static int convertStrToIntMonth(string month);
	static int convertDayOfWeekToIntDaysToAdd(string query, bool isNextWeek);
	Item::PriorityLevel convertStrToPriorityLevel(string priority);
	static void convertStringToLowercase(string &myString);
	vector <Item*> convertItemNumsToItemPtrs(string itemNumsStr);
	vector <string> convertStringToVector(string inputString);
	string convertVectorToString(vector<string>::iterator start, vector<string>::iterator end);
	void trimWordFromString(string &originalString, string toTrim);
	CmdEditItem* constructRespectiveCmdEdit(int fieldNum, string newFieldInfo);
public:
	static const string Parser::ERROR_INVALID_ITEM_NO;
	static const string Parser::ERROR_INVALID_FIELD_NO;
	static const string Parser::ERROR_INVALID_COMMAND;
	static const string Parser::ERROR_MISSING_TITLE;
	static const string Parser::ERROR_MISSING_CATEGORY;
	static const string Parser::ERROR_INVALID_BRACKETS;
	static const string Parser::ERROR_INVALID_PRIORITY;
	static const string Parser::ERROR_LOGIC_START_END;
	static const string Parser::ERROR_EMPTY_DELETE;
	static const string Parser::ERROR_EMPTY_MARK;
	Command* stringToCommand(string userCommand);
	Parser(void);
	~Parser(void);


};

