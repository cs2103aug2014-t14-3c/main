#pragma once
#include "CommandLogic.h"
class Redo :
	public CommandLogic
{
public:
	Redo();
	~Redo();
	
	vector<string> execute();
};

