//@author A0116781A
//
//------------------------------------------
//This is the CmdInitialiseBank class. It is 
//executed when JustAddIt is opened and 
//handles the loading in of existing items  
//into the software. 
//
//The software is initialised by reading the
//textfile stored in memory and translating 
//it into a bank in the software for easier 
//manipulation. After loading the data, the 
//CmdHome class is called to create the 
//home screen for the software. 
//
//This command will not check for errors. 
//Instead, exceptions are handled by the 
//method in ItemBank and CmdHome.
//------------------------------------------

#pragma once
#include "stdafx.h"
#include "Command.h"
#include "ItemBank.h"
#include "CmdHome.h"

class CmdInitialiseBank :
	public Command {
private:
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_WELCOME_PAGE_INFO;

public:
	CmdInitialiseBank(void);
	~CmdInitialiseBank(void);

	vector<string> execute();
};

