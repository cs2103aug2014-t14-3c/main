#include "stdafx.h"
#include "Search.h"


Search::Search(string searchTerm) {
	_searchTerm = searchTerm;
}


Search::~Search() {
}

vector<string> Search::getItem(string keyword) {
}

//From CE2, will be changed later
vector<string> Search::execute() {
	ifstream fin(fileName); 
	string itemsToBeSearched; 
	while(getline(fin, itemsToBeSearched)) {
		temporaryStorage.push_back(itemsToBeSearched);
	}
	string contentAfterSearching; 
	int sizeOfItemList = temporaryStorage.size(); 
	for (int i = 0; i < sizeOfItemList; i++) { 
		for (int start = 0; start <= temporaryStorage[i].length(); start++) { 
			if (!((temporaryStorage[i]).substr(start, temporaryStorage[i].length())).find(keyword)) { 
				showUser(temporaryStorage[i] + "\n"); 
				contentAfterSearching.append(temporaryStorage[i]); break;} 
		}
	}
//return vector<string> item
//pushback
}