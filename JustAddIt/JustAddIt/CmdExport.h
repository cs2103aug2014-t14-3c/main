#pragma once
#include "Command.h"
#include "Exporter.h"

class CmdExport :
	public Command
{
public:
	CmdExport(void);
	~CmdExport(void);
	vector<string> CmdExport::execute();
};