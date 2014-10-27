#pragma once
#include "stdafx.h"
#include "Command.h"
#include "CmdHome.h"
#include "CmdGoToListView.h"
#include "OutputControl.h"

class CmdGoToBaseScreen :
	public Command
{

private:
	Command* baseScreenCmd;

public:

	CmdGoToBaseScreen(OutputControl::CurrentScreenType currentBaseScreen);
	~CmdGoToBaseScreen(void);
	vector<string> CmdGoToBaseScreen::execute();
};