#pragma once
//@author A0110770U
//------------------------------------------
//CmdGoToBaseScreen acts as a function to allow the
//user to go to the base screen.
//
//Depending on the information from OutputControl,
//it will return the user to the main screen that
//the user was at previously.
//
//CmdGoToBaseScreen will not throw exceptions.
//If there is an error in reading a screen from
//OutputControl, it will return the user to Home.
//------------------------------------------
#include "stdafx.h"
#include "Command.h"
#include "CmdHome.h"
#include "CmdGoToListView.h"
#include "CmdSearch.h"
#include "CmdShowOverdueDeadlines.h"
#include "OutputControl.h"

class CmdGoToBaseScreen :
	public Command
{

private:
	Command* _baseScreenCmd;

public:

	CmdGoToBaseScreen(OutputControl::CurrentScreenType currentBaseScreen);
	~CmdGoToBaseScreen(void);
	vector<string> CmdGoToBaseScreen::execute();
};