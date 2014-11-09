//@author A0116781A
//
//------------------------------------------
//This is the CmdUndo class. It will execute 
//a undo operation whenever it is called by 
//the user. 
//
//The operation is done by calling the undo 
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

class CmdUndo :
	public Command
{
public:
	CmdUndo(void);
	~CmdUndo(void);

	vector<string> execute();
	void addToActionLog();
};

