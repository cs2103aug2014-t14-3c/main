//@author A0128461H
#pragma once
#include "Command.h"
#include "ItemBank.h"
#include "DisplayScreenConstructor.h"

class CmdSearch :
	public Command 
{
private:
	string _searchKeyword;
	
public:
	CmdSearch(string keyword);
	~CmdSearch(void);

	vector<string> CmdSearch::execute();
};

