#pragma once
#include "stdafx.h"
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"
#include "CmdHome.h"

class CmdClearAllDone :
	public Command
{
public:
	CmdClearAllDone(void);
	~CmdClearAllDone(void);
	vector<string> CmdClearAllDone::execute();
};