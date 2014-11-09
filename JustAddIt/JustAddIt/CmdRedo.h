//@author A0116781A
//
//------------------------------------------
//This is the CmdRedo class. It will execute 
//a redo operation whenever it is called by 
//the user. 
//
//The operation is done by calling the redo 
//operation in the ActionLog. 
//
//This command will not check for errors. 
//Instead, exceptions are handled by the 
//method in ActionLog.
//------------------------------------------

#pragma once
#include "command.h"
#include "ActionLog.h"
#include "CmdGoToBaseScreen.h"

class CmdRedo :
	public Command
{
public:
	CmdRedo(void);
	~CmdRedo(void);

	vector<string> execute();
	void addToActionLog();
};

