#include "stdafx.h"
#include "CmdInitialiseBank.h"

CmdInitialiseBank::CmdInitialiseBank(void)
{
}

CmdInitialiseBank::~CmdInitialiseBank(void)
{
}

vector<string> CmdInitialiseBank::execute() {
	ItemBank::initialiseBank();

	DisplayScreenConstructor* displayScreenConstructor = DisplayScreenConstructor::getInstance();
	outputMessageStorage.clear();
	outputMessageStorage = displayScreenConstructor->constructHomeScreen();

	OutputControl::setCurrentScreen(OutputControl::CurrentScreenType::HOME_SCREEN);

	return outputMessageStorage;
}