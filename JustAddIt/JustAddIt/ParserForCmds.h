#pragma once
#include "stdafx.h"
#include "OutputControl.h"
using namespace std;

class ParserForCmds { 


public:

	ParserForCmds(void);
	~ParserForCmds(void);
	CommandType determineCommandType(string userCommand, OutputControl::CurrentScreenType currentScreen);
	CommandType determineCommandType_HomeScreen(string userCommand);
	CommandType determineCommandType_EditScreen(string userCommand);
	CommandType determineCommandType_SearchResultsScreen(string userCommand);
	CommandType determineCommandType_ToDoListView(string userCommand);
	CommandType determineCommandType_CalendarView(string userCommand);
	CommandType determineCommandType_OverdueTasksScreen(string userCommand);
	CommandType determineCommandType_GoToBaseScreen();

private:

};
