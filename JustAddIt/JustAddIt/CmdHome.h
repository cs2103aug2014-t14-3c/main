#pragma once
//@author A0110770U
//------------------------------------------
//CmdHome acts as a function to return the
//user to the home screen.
//
//On the home screen, it shows the 
//items that are occuring in the next 
//week from the current time. 
//
//To edit the home screen template, modify
//the text file under Templates folder.
//
//CmdHome will not throw exceptions.
//------------------------------------------
#include "Command.h"
#include "DisplayScreenConstructor.h"

class CmdHome :
	public Command
{
private:
	struct tm _currentTime;

	void updateOutputControl();
	vector<string> storeHomeScreenForDisplay();

public:
	CmdHome(void);
	~CmdHome(void);
	vector<string> CmdHome::execute();
};