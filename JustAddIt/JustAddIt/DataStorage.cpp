//@author A0108397W
#include "stdafx.h"
#include "DataStorage.h"

const string DataStorage::SPACE = " ";
const string DataStorage::EMPTY_STRING = "";
const string DataStorage::FILE_NAME = "JustAddIt/JustAddIt_ItemBank.txt";
const int DataStorage::NUM_OF_ATTRIBUTES_PER_ITEM = 9;
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

//This function writes the details of the Items stored in the program into the computer's local memory - in the format of a
//text file
void DataStorage::writeToFile(vector<string>itemDetails) {
	ofstream mytextfile;
	mytextfile.open(FILE_NAME);

	for (vector<string>::iterator iter = itemDetails.begin(); iter != itemDetails.end(); iter++) {
		mytextfile << *iter << endl;
	}

	mytextfile.close();
}

//This function extracts the Item details stored inside the computer's local memory (in the form of a text file)
//and returns it to ItemBank as a vector<string>
vector<string> DataStorage::readFromLocalMemory() {
	vector<string> itemDetails;
	string dummyLine;
	ifstream mytextfile;
	mytextfile.open(FILE_NAME);

	while (!mytextfile.eof()) {

		getline(mytextfile, dummyLine);

		if (dummyLine != EMPTY_STRING) {
			dummyLine = trimWhiteSpaceOnLeft(dummyLine);
			itemDetails.push_back(dummyLine);
		}
	}
	mytextfile.close();

	if (isCorrupted(itemDetails) == true) {
		itemDetails.clear();
	}
	return itemDetails;
}

inline string DataStorage::trimWhiteSpaceOnLeft(const string& inputString) {
	return inputString.substr( inputString.find_first_not_of(SPACE));
}

//This function checks to see if the local memory (text file) has been altered by removing any content or adding addItional content
bool DataStorage::isCorrupted(vector<string> itemDetails) {
	bool isCorrupted = false;

	if (itemDetails.size()%NUM_OF_ATTRIBUTES_PER_ITEM != 0) {
		isCorrupted = true;
	}

	return isCorrupted;
}