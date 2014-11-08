//@author A0128461H
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(CmdAdd)
	{
	public:

		TEST_METHOD(CmdAddTest)
		{
			Item* addTest1 = new Item;
			Item* addTest2 = new Item;
			ItemBank* itemPointer = ItemBank::getInstance();

			addTest1 -> setTitle("finish JustAddIt");
			addTest1 -> setDescription("cs2103 project");
			addTest1 -> setStartDate(4, 8);
			addTest1 -> setStartTime(8, 0);
			addTest1 -> setEndDate(10, 11);
			addTest1 -> setEndTime(12, 0);
			addTest1 -> setPriority("High");
			addTest1 -> setCategory("Project");
			addTest1 -> setVenue("PGP");

			Assert::AreEqual(itemPointer -> addToBank(addTest1), false);
			Assert::AreEqual(itemPointer -> getBankSize(), 1);

			addTest2 -> setTitle("finish network assignment");
			addTest2 -> setDescription("cs2105 assignment");
			addTest2 -> setStartDate(15, 11);
			addTest2 -> setStartTime(8, 0);
			addTest2 -> setEndDate(17, 11);
			addTest2 -> setEndTime(12, 0);
			addTest2 -> setPriority("High");
			addTest2 -> setCategory("Assignment");
			addTest2 -> setVenue("PGP");

			Assert::AreEqual(itemPointer -> addToBank(addTest2), false);
			Assert::AreEqual(itemPointer -> getBankSize(), 2);

			itemPointer -> clearBank();
		}
	};
}