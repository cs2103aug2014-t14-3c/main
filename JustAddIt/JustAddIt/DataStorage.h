#pragma once
#include "ItemBank.h"

class DataStorage
{
private:
	static string filename;
	static DataStorage* dataStorage;

	DataStorage(void);
	static inline string DataStorage::trimWhiteSpaceOnLeft(const string& inputString);

public:
	static DataStorage* getInstance(void);
	~DataStorage(void);

	static void writeToFile(vector<string>itemsToBeWrittenToFile);
	vector<string> readToBank();
};

