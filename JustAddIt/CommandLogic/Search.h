#pragma once
#include "CommandLogic.h"

class Search :
	public CommandLogic
{
private:
	string _searchTerm;

public:
	Search(string searchTerm);
	~Search();

	vector<string> getItem(string keyword);
	vector<string> execute();
};
