#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(CmdAdd)
	{
	public:
		
		TEST_METHOD(CmdAddTest) // all positive test case *using multiple input
		{
			Item* itemPtr = new Item;
			Item* itemPtr2 = new Item;
			ItemBank* itemPointer = ItemBank::getInstance();

			itemPtr -> setTitle("finish JustAddIt");
			itemPtr -> setDescription("cs2103 project");
			itemPtr -> setStartDate(4, 8);
			itemPtr -> setStartTime(8, 0);
			itemPtr -> setEndDate(10, 11);
			itemPtr -> setEndTime(12, 0);
			itemPtr -> setPriority("High");
			itemPtr -> setCategory("Project");
			itemPtr -> setVenue("PGP");

			Assert::AreEqual(itemPointer -> addToBank(itemPtr), false);
			Assert::AreEqual(itemPointer -> getBankSize(), 1);

			itemPtr2 -> setTitle("finish network assignment");
			itemPtr2 -> setDescription("cs2105 assignment");
			itemPtr2 -> setStartDate(4, 8);
			itemPtr2 -> setStartTime(8, 0);
			itemPtr2 -> setEndDate(10, 11);
			itemPtr2 -> setEndTime(12, 0);
			itemPtr2 -> setPriority("High");
			itemPtr2 -> setCategory("Assignment");
			itemPtr2 -> setVenue("PGP");

			Assert::AreEqual(itemPointer -> addToBank(itemPtr2), true);
			Assert::AreEqual(itemPointer -> getBankSize(), 2);

			itemPointer -> clearBank();
		}
	};
}