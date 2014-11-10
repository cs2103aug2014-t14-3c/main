#pragma once
//@author A0110770U
//------------------------------------------
//ParserForCmds acts as a helper to Parser
//by understanding user commands, depending on
//which screen the user is at currently.
//
//User commands for each screen can be updated
//by modifying the values used for comparison
//in the respective functions.
//
//If new screens are added, follow a similar 
//format to the determineCommandType
//functions that are available.
//
//ParserForCmds will throw exceptions if it detects
//any invalid command.
//------------------------------------------
#include "stdafx.h"
#include "OutputControl.h"
using namespace std;

class ParserForCmds { 


public:

	ParserForCmds(void);
	~ParserForCmds(void);
	CommandType determineCommandType(string userCommand, OutputControl::CurrentScreenType currentScreen);


private:
	CommandType determineCommandType_HomeScreen(string userCommand);
	CommandType determineCommandType_EditScreen(string userCommand);
	CommandType determineCommandType_SearchResultsScreen(string userCommand);
	CommandType determineCommandType_ToDoListView(string userCommand);
	CommandType determineCommandType_OverdueTasksScreen(string userCommand);
	CommandType determineCommandType_GoToBaseScreen();
<<<<<<< HEAD
=======

private:
	static const string ERROR_INVALID_COMMAND;

>>>>>>> aa78c47ea4de706124cca010337ca5158c248961
};
