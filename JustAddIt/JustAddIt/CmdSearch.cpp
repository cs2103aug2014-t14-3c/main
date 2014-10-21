#include "stdafx.h"
#include "CmdSearch.h"

CmdSearch::CmdSearch(string keyword) {
	searchKeyword = keyword;
}

CmdSearch::~CmdSearch(void) {
}

vector<string> CmdSearch::execute() {
	ifstream fin("JustAddIt_ItemBank.txt");
	string itemsToBeSearched;
	while(getline(fin, itemsToBeSearched)) {
		temporaryStorage.push_back(itemsToBeSearched);
	}

	int sizeOfItemList = temporaryStorage.size();
	for (int i = 0; i < sizeOfItemList; i++) {
		for (int start = 0; start <= temporaryStorage[i].length(); start++) {
			if (!((temporaryStorage[i]).substr(start, temporaryStorage[i].length())).find("")) {
				//Put the keyword you want to search inside the double quotation marks of .find("")
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