#include "stdafx.h"
#include "CmdSearch.h"

CmdSearch::CmdSearch(vector<Item>::iterator itemPtr) {
	_itemPtr = itemPtr;
}

CmdSearch::~CmdSearch(void) {
}

vector<string> CmdSearch::execute() {
}