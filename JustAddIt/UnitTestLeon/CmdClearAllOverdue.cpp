#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CmdClearAllOverdue)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ItemBank* itemPointer = new ItemBank;
			Item* task1 = new Item;
			Item* task2 = new Item;
			Item* task3 = new Item;
			task1->setItemType("deadline");
			task2->setItemType("event");
			task3->setItemType("task");
			itemPointer->addToBank(task1);
			itemPointer->addToBank(task2);
			itemPointer->addToBank(task3);
			time_t currentTime;
			time(&currentTime);

			Assert::AreEqual(itemPointer->getBankSize(), 3);
			itemPointer->deleteAllOverdueDeadlinesFromBank();
			Assert::AreEqual(itemPointer->getBankSize(), 2);
		}
	};
}