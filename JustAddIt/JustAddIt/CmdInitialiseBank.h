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

