#pragma once
#include "stdafx.h"
#include "Command.h"

class CmdExport :
	public Command {

public:

	static const string MESSAGE_EXPORT_SUCCESSFUL;

	CmdExport(void);
	~CmdExport(void);
	vector<string> CmdExport::execute();

};