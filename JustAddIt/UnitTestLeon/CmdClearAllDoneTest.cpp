//@author: A0128461H
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CmdClearAllDone)
	{
	public:
		
		TEST_METHOD(CmdClearAllDoneTest)
		{
			Item* itemTest1 = new Item;
			Item* itemTest2 = new Item;
			ItemBank* itemPointer = ItemBank::getInstance();

			itemTest1 -> setTitle("study cs2103");
			itemTest1 -> setItemType("task");
			itemPointer -> addToBank(itemTest1);
			Assert::AreEqual(itemPointer -> getBankSize(), 1);

			itemTest1 -> toggleDone();
			itemPointer -> deleteDoneItems();
			Assert::AreEqual(itemPointer -> getBankSize(), 0);

			itemTest2 -> setTitle("study cs2105");
			itemTest2 -> setItemType("task");
			itemPointer -> addToBank(itemTest1);
			Assert::AreEqual(itemPointer -> getBankSize(), 1);

			try {
				itemPointer -> deleteDoneItems();
			}
			catch (exception &e) {
				Assert::AreEqual("No more done items to be cleared!", e.what());
			}

			itemPointer->clearBank();
		}
	};
}