#pragma once
//@author A0110770U
//-----------------------------------------------
//This is the Command super class in which
//all other Cmds inherit from. Command objects 
//should not be created.
//
//When adding new Cmds, inherit as a subclass of
//Command. New Cmds should have should a execute
//function, similar to existing Cmds.
//-----------------------------------------------

#include "stdafx.h"

#include "ItemBank.h"
#include "OutputControl.h"

using namespace std;

class Command
{
protected:
	vector<string> outputMessageStorage;

public:
	Command(void);
	~Command(void);
	virtual vector<string> execute();
};