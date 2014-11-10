//@author A0108397W
#pragma once
#include "ItemBank.h"

class DataStorage
{
private:
	static const string SPACE;
	static const string EMPTY_STRING;
	static const string FILE_NAME;
	static const int NUM_OF_ATTRIBUTES_PER_ITEM;
	static DataStorage* dataStorage;

	DataStorage(void);
	static inline string trimWhiteSpaceOnLeft(const string& inputString);
	bool isCorrupted(vector<string> itemDetails);

public:
	static DataStorage* getInstance(void);
	~DataStorage(void);
	static void writeToFile(vector<string> items);
	vector<string> readFromLocalMemory();
};

