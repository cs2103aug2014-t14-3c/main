//@author A0108397W
#pragma once
#include "stdafx.h"
#include "Command.h"

class CmdExport :
	public Command {
private:
	static const string MESSAGE_EXPORT_SUCCESSFUL;

public:
	CmdExport(void);
	~CmdExport(void);
	vector<string> execute();
};