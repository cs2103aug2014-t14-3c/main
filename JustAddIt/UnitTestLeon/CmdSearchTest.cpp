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
			// TODO: Your test code here
			ItemBank* itemPointer = ItemBank::getInstance();
			itemPointer->clearBank();
			Item* task = new Item;
			string title = "study";
			string testing = "event";
			string description = "study cs2103";
			task->setItemType("event");
			task->setTitle("testing");
			itemPointer->addToBank(task);
			Assert::AreEqual(itemPointer->getBankSize(), 1);
			Assert::AreEqual(itemPointer->searchKeyword(task->getItemTypeInString(), testing), true);
		}
	};
}