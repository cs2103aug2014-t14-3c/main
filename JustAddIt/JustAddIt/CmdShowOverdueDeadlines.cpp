#include "stdafx.h"
#include "CmdShowOverdueDeadlines.h"


CmdShowOverdueDeadlines::CmdShowOverdueDeadlines(void)
{
	time_t myTempTime;
	time(&myTempTime);
	_currentTime = myTempTime;
}


CmdShowOverdueDeadlines::~CmdShowOverdueDeadlines(void)
{
}

vector<string> CmdShowOverdueDeadlines::execute() {
	vector<Item*>itemsToBeDisplayed;

	itemsToBeDisplayed = ItemBank::getOverdueDeadlines();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->clearScreen();
	outputMessageStorage = displayScreenConstructor->constructOverdueScreen(itemsToBeDisplayed);
	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::OVERDUE_TASKS_SCREEN);
	OutputControl::setCurrentBaseScreen(OutputControl::CurrentScreenType::OVERDUE_TASKS_SCREEN);
	//update outputcontrol with currently displayed
	OutputControl::setCurrentDisplayedItemList(itemsToBeDisplayed);
	return outputMessageStorage;
}