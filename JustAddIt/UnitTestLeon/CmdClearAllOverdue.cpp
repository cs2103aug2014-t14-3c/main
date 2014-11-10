//@author A0128461H
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CmdClearAllOverdue)
	{
	public:
		
		TEST_METHOD(CmdClearAllOverdueTest)
		{
			Item* itemTest1 = new Item;
			Item* itemTest2 = new Item;
			Item* itemTest3 = new Item;
			ItemBank* itemPointer = ItemBank::getInstance();
			itemTest1 -> setItemType("deadline");
			itemTest2 -> setItemType("event");
			itemTest3 -> setItemType("task");
			itemPointer -> addToBank(itemTest1);
			itemPointer -> addToBank(itemTest2);
			itemPointer -> addToBank(itemTest3);
			time_t currentTime;
			time(&currentTime);

			Assert::AreEqual(itemPointer -> getBankSize(), 3);
			itemPointer -> deleteOverdueDeadlines();
			Assert::AreEqual(itemPointer -> getBankSize(), 2);

			try {
				itemPointer -> deleteOverdueDeadlines();
			}
			catch (exception &e) {
				Assert::AreEqual("No more overdue deadlines to be cleared!", e.what());
			}

			itemPointer->clearBank();
		}
	};
}