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
			ItemBank* itemPointer = ItemBank::getInstance();

			itemTest1 -> setTitle("study cs2103");
			itemTest1 -> setItemType("task");
			itemPointer -> addToBank(itemTest1);
			Assert::AreEqual(itemPointer -> getBankSize(), 1);

			itemTest1 -> toggleDone();
			itemPointer -> deleteDoneItems();
			Assert::AreEqual(itemPointer -> getBankSize(), 0);

			itemPointer->clearBank();
		}
	};
}