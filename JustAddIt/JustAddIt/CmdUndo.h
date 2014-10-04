#pragma once
#include "command.h"
class CmdUndo :
	public Command
{
public:
	CmdUndo(void);
	~CmdUndo(void);
};

