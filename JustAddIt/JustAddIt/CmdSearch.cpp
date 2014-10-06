#include "stdafx.h"
#include "CmdSearch.h"

CmdSearch::CmdSearch(string keyword) {
	searchKeyword = keyword;
}

CmdSearch::~CmdSearch(void) {
}

vector<string> CmdSearch::execute() {
	int sizeOfItemList = ItemBank::bank.size();
	for (int i = 0; i < sizeOfItemList; i++) {
		for (int start = 0; start <= ItemBank::bank[i]->getTitle().length(); start++) {
				if (!((temporaryStorage[i]).substr(start, temporaryStorage[i].length())).find(searchKeyword)) {
					//showUser(temporaryStorage[i] + "\n");
					contentAfterSearching.push_back(temporaryStorage[i]);
					break;
				}
		}
	}
	for (int i = 0; i < sizeOfItemList; i++) {
		temporaryStorage.pop_back();
	}
	return contentAfterSearching;
}