#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CmdSearch)
	{
	public:
		
		TEST_METHOD(CmdSearchTest)
		{
			Item* itemSearchTest1 = new Item;
			Item* itemSearchTest2 = new Item;
			ItemBank* itemPointer = ItemBank::getInstance();
			itemPointer -> clearBank();

			itemSearchTest1 -> setItemType("deadline");
			itemSearchTest1 -> setTitle("search testing");
			itemSearchTest1 -> setDescription("For JustAddIt");
			itemSearchTest1 -> setStartDate(4, 8);
			itemSearchTest1 -> setStartTime(8, 0);
			itemSearchTest1 -> setEndDate(10, 11);
			itemSearchTest1 -> setEndTime(12, 0);
			itemSearchTest1 -> setPriority("Medium");
			itemSearchTest1 -> setCategory("Individual Component");
			itemSearchTest1 -> setVenue("PGP");
			itemPointer -> addToBank(itemSearchTest1);

			itemSearchTest2 -> setItemType("task");
			itemSearchTest2 -> setTitle("overall testing");
			itemSearchTest2 -> setDescription("For JustAddIt");
			itemSearchTest2 -> setPriority("High");
			itemSearchTest2 -> setCategory("Group Project");
			itemSearchTest2 -> setVenue("UTown");
			itemPointer -> addToBank(itemSearchTest2);

			Assert::AreEqual(itemPointer -> getBankSize(), 2);

			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest1 -> getItemTypeInString(), "dead"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest1 -> getTitle(), "test"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest1 -> getDescription(), "AddIt"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest1 -> getStartDateInString(), "4"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest1 -> getEndDateInString(), "10"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest1 -> getPriorityInString(), "Med"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest1 -> getCategory(), "Individual Component"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest1 -> getVenue(), "PGP"), true);

			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest2 -> getItemTypeInString(), "dead"), false);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest2 -> getTitle(), "test"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest2 -> getDescription(), "AddIt"), true);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest2 -> getStartDateInString(), "4"), false);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest2 -> getEndDateInString(), "10"), false);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest2 -> getPriorityInString(), "Med"), false);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest2 -> getCategory(), "Individual Component"), false);
			Assert::AreEqual(itemPointer -> searchKeyword(itemSearchTest2 -> getVenue(), "PGP"), false);
		}
	};
}