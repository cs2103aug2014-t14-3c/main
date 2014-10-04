#pragma once
#include "ItemBank.h"

class DataStorage
{
private:
	static string filename;

public:
	static void writeToFile();
	static void readToBank();
};

