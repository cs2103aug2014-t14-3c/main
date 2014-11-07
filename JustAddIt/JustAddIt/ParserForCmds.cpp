//@LokeJunJie A0110770
#include "stdafx.h"
#include "ParserForCmds.h"

ParserForCmds::ParserForCmds(void)
{
}


ParserForCmds::~ParserForCmds(void)
{
}

CommandType ParserForCmds::determineCommandType(string userCommand, OutputControl::CurrentScreenType currentScreen) {
	//universal commands
	if (userCommand == "add" || userCommand == "a" || userCommand == "ad") {
		return ADD;
	}
	if (userCommand == "search" || userCommand == "s" || userCommand == "se"
		 || userCommand == "sea" || userCommand == "sear" || userCommand == "searc") {
		return SEARCH;
	}
	if (userCommand == "undo" || userCommand == "u" || userCommand == "un" || userCommand == "und") {
		return UNDO;
	}
	if (userCommand == "redo" || userCommand == "r" || userCommand == "re" || userCommand == "red") {
		return REDO;
	}
	if (userCommand == "home" || userCommand == "h" || userCommand == "ho" || userCommand == "hom") {
		return HOME;
	}
	if (userCommand == "export" || userCommand == "ex" || userCommand == "exp"
		 || userCommand == "expo" || userCommand == "expor") {
		return EXPORT;
	}


	switch (currentScreen) {
	case OutputControl::HOME_SCREEN: {
		return determineCommandType_HomeScreen(userCommand);
		break;
			}

	case OutputControl::EDIT_SCREEN: {
		return determineCommandType_EditScreen(userCommand);
		break;
			}

	case OutputControl::SEARCH_RESULTS_SCREEN: {
		return determineCommandType_SearchResultsScreen(userCommand);
		break;
			}

	case OutputControl::TO_DO_LIST_VIEW: {
		return determineCommandType_ToDoListView(userCommand);
		break;
			}

	case OutputControl::OVERDUE_TASKS_SCREEN: {
		return determineCommandType_OverdueTasksScreen(userCommand);
		break;
			 }

	default: {
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
		break;
			 }
	}

}

CommandType ParserForCmds::determineCommandType_HomeScreen(string userCommand){

	if (userCommand == "t") {
		return VIEW_TODOLIST;
	}else if (userCommand == "c") {
		return VIEW_CALENDAR;
	}else if (userCommand == "o") {
		return VIEW_OVERDUE;
	}else{
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
	}

}
CommandType ParserForCmds::determineCommandType_EditScreen(string userCommand){
	
	if (userCommand == "e") {
		return EDIT_FIELD;
	}else if (userCommand == "o" || userCommand == "") {
		return determineCommandType_GoToBaseScreen();
	}else if (userCommand == "d") {
		return DELETE;
	}else{
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
	}

}

CommandType ParserForCmds::determineCommandType_SearchResultsScreen(string userCommand){
	if (userCommand == "e") {
		return EDIT_ITEM;
	}else if (userCommand == "m") {
		return MARK;
	}else if (userCommand == "d") {
		return DELETE;
	}else if (userCommand == "c") {
		return CLEAR_ALL_DONE;
	}else{
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
	}


}
CommandType ParserForCmds::determineCommandType_ToDoListView(string userCommand){
	if (userCommand == "e") {
		return EDIT_ITEM;
	}else if (userCommand == "m") {
		return MARK;
	}else if (userCommand == "d") {
		return DELETE;
	}else if (userCommand == "c") {
		return CLEAR_ALL_DONE;
	}else{
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
	}

}

CommandType ParserForCmds::determineCommandType_OverdueTasksScreen(string userCommand){
	
	if (userCommand == "m") {
		return MARK;
	}else if (userCommand == "d") {
		return DELETE;
	}else if (userCommand == "c") {
		return CLEAR_ALL_OVERDUE;
	}else{
		throw invalid_argument("Invalid command! Please enter a valid command from the menu.");
	}
	
}

CommandType ParserForCmds::determineCommandType_GoToBaseScreen(){

	switch(OutputControl::getCurrentBaseScreen()) {
		case OutputControl::CurrentScreenType::HOME_SCREEN:{
			return HOME;
			break;
														   }
		case OutputControl::CurrentScreenType::TO_DO_LIST_VIEW:{
			return VIEW_TODOLIST;
			break;									
															   }
		case OutputControl::CurrentScreenType::SEARCH_RESULTS_SCREEN:{
			return VIEW_LAST_SEARCH;
			break;									
															   }
		case OutputControl::CurrentScreenType::OVERDUE_TASKS_SCREEN:{
			return VIEW_OVERDUE;
			break;									
															   }
		default:{
			return HOME;
			break;
				}
	}
}
