#include "stdafx.h"
#include "DataStorage.h"

string fileName = "JustAddIt_ItemBank.txt";
DataStorage* DataStorage::dataStorage = NULL;

DataStorage::DataStorage(void) {
}

DataStorage::~DataStorage(void) {
}

DataStorage* DataStorage::getInstance(void) {
	if (dataStorage == NULL) {
		dataStorage = new DataStorage();
	}
	return dataStorage;
}

void DataStorage::writeToFile(vector<string>itemsToBeWrittenToFile) {
	ofstream mytextfile;
	mytextfile.open(fileName);
	vector<string>::iterator iter;

	for (iter = itemsToBeWrittenToFile.begin(); iter != itemsToBeWrittenToFile.end(); iter++) {
		mytextfile << *iter << endl;
	}

	mytextfile.close();
	return;
}

vector<string> DataStorage::readToBank() {
	vector<string> items;
	string dummyLine;
	ifstream mytextfile;
	mytextfile.open(fileName);

	while (!mytextfile.eof()) {
		getline(mytextfile, dummyLine);
		if (dummyLine != "") {
		dummyLine = trimWhiteSpaceOnLeft(dummyLine);
		items.push_back(dummyLine);
		}
		else {
		continue;
		}
	}
	mytextfile.close();
	return items;
}

inline string DataStorage::trimWhiteSpaceOnLeft(const string& inputString) {
	return inputString.substr( inputString.find_first_not_of(" "));
}