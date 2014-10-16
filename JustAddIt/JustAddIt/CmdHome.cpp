#include "stdafx.h"
#include "CmdHome.h"

CmdHome::CmdHome(void) {
}

CmdHome::~CmdHome(void)
{
}

vector<string> CmdHome::execute() {

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructHomeScreen();

	return outputMessageStorage;
}

//void CmdHome::setPageCommands() {
//	outputMessageStorage.push_back(FORMAT_DIVIDER);
//
//	outputMessageStorage.push_back(PAGE_COMMAND_UNDO);
//	outputMessageStorage.push_back(PAGE_COMMAND_CALENDAR_VIEW);
//	outputMessageStorage.push_back(PAGE_COMMAND_TO_DO_LIST_VIEW);
//	outputMessageStorage.push_back(PAGE_COMMAND_OVERDUE_TASKS);
//
//	outputMessageStorage.push_back(FORMAT_DIVIDER);
//
//	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::HOME_SCREEN);
//}