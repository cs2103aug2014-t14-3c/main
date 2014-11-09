//@author A0116781A-unused
//
//-----------------------------------
//This is the interface receiver from
//the GUI to the Logic components. 
//The class has been deprecated.
//-----------------------------------

#pragma once
#include "stdafx.h"
#include "Executor.h"

class IReceiver
{
private:
	static vector<string> outputMessageStorage;

public:
	static vector<string> initialise();
	static vector<string> receive(string userCommand);
};

