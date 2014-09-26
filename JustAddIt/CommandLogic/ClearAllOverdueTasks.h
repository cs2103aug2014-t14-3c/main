#pragma once
#include "CommandLogic.h"
class ClearAllOverdueTasks :
	public CommandLogic
{
public:
	ClearAllOverdueTasks();
	~ClearAllOverdueTasks();

	vector<string> execute();
};

