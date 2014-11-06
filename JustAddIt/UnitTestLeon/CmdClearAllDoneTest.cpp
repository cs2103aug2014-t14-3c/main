#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CmdClearAllDoneTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			ItemBank* itemPointer = new ItemBank;
			Item* task = new Item;
			string title = "study";
			string testing = "event";
			string description = "study cs2103";
			task->setItemType("event");
			task->setTitle("testing");
			itemPointer->addToBank(task);
			Assert::AreEqual(itemPointer->getBankSize(), 1);
			Assert::AreEqual(itemPointer->searchKeywordInItemAttribute(task->getItemType(), testing), true);
		}
	};
}