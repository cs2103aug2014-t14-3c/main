#include "stdafx.h"
#include "CmdSearch.h"

CmdSearch::CmdSearch(string keyword) {
	itemsToBeSearched = keyword;
}

CmdSearch::~CmdSearch(void) {
}

string CmdSearch::execute() {
	//ifstream fin(filename);
	//while(getline(fin, itemsToBeSearched)) {
		//temporaryStorage.push_back(itemsToBeSearched);
	//}

	string contentAfterSearching;
	int sizeOfItemList = temporaryStorage.size();
	for (int i = 0; i < sizeOfItemList; i++) {
		for (int start = 0; start <= temporaryStorage[i].length(); start++) {
				if (!((temporaryStorage[i]).substr(start, temporaryStorage[i].length())).find(itemsToBeSearched)) {
					//showUser(temporaryStorage[i] + "\n");
					contentAfterSearching.append(temporaryStorage[i]);
					break;
				}
			}
		}
	
	for (int i = 0; i < sizeOfItemList; i++) {
		temporaryStorage.pop_back();
	}
	return contentAfterSearching;
}