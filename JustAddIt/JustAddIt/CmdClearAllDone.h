//@author A0128461H
#pragma once
#include "stdafx.h"
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"
#include "CmdGoToBaseScreen.h"
#include "ActionLog.h"

class CmdClearAllDone :
	public Command
{
public:
	CmdClearAllDone(void);
	~CmdClearAllDone(void);
	vector<string> CmdClearAllDone::execute();
};