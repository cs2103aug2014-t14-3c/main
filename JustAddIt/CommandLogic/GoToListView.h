#pragma once
#include "CommandLogic.h"
class GoToListView :
	public CommandLogic
{
public:
	GoToListView();
	~GoToListView();

	vector<string> execute();

};

