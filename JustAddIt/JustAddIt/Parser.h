#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <ctype.h>
#include <sstream>
#include <iterator>
#include "Command.h"
#include "CmdAddItem.h"
#include "CmdSearch.h"


enum CommandType {
	ADD, SEARCH, EDIT
};

class Parser
{
public:
	void embedDetailsInItem(Item* myItem, string stringDetails);
	void detectTitleAndEmbed(Item* myItem, string stringDetails);
	void detectTimeAndEmbed(Item* myItem, string stringDetails);
	void detectDateAndEmbed(Item* myItem, string stringDetails);
	int convertStringToIntHour(string stringTime);
	int convertStringToIntMin(string stringTime);
	int convertStrToIntMonth(string month);
	void convertStringToLowercase(string &myString);
	CommandType determineCommandType(string userCommand);
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

