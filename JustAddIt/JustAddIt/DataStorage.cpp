#include "stdafx.h"
#include "DataStorage.h"

string fileName = "JustAddIt/JustAddIt_ItemBank.txt";
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

void DataStorage::writeToFile(vector<string>items) {
	ofstream mytextfile;
	mytextfile.open(fileName);
	vector<string>::iterator iter;

	for (iter = items.begin(); iter != items.end(); iter++) {
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
	}
	mytextfile.close();
	return items;
}

inline string DataStorage::trimWhiteSpaceOnLeft(const string& inputString) {
	return inputString.substr( inputString.find_first_not_of(" "));
}
