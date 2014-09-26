#pragma once
#include "CommandLogic.h"

class Undo :
	public CommandLogic
{
public:
	Undo();
	~Undo();

	vector<string> execute();
};

