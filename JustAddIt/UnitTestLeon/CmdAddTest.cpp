#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string FILL = "This is a random filler text to test code";
const string DATE = "Saturday 15 Nov 2014 08:00AM";

namespace UnitTest
{		
	TEST_CLASS(CmdAdd)
	{
	public:
		
		TEST_METHOD(CmdAddTest) // all positive test case *using multiple input
		{
			Item* itemPtr = new Item;
			ItemBank* itemPointer = ItemBank::getInstance();

			itemPtr->setTitle("finish JustAddIt");
			itemPtr->setDescription("cs2103 project");
			itemPtr->setStartDate(4, 8);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(10, 11);
			itemPtr->setEndTime(12, 0);
			itemPtr->setPriority("High");
			itemPtr->setCategory("Project");
			itemPtr->setVenue("PGP");
			
			itemPointer -> addToBank(itemPtr);

			Assert::AreEqual(itemPointer->getBankSize(), 1);
			
			itemPointer->clearBank();
		}
	};
}