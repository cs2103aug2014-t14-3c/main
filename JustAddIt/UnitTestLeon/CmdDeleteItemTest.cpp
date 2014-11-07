//@author A0108397W
#include "stdafx.h"
#include "CppUnitTest.h"
#include "OutputControl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

enum CurrentScreenType { 
	HOME_SCREEN, 
	EDIT_SCREEN, 
	SEARCH_RESULTS_SCREEN, 
	TO_DO_LIST_VIEW, 
	CALENDAR_VIEW, 
	OVERDUE_TASKS_SCREEN 
};

namespace UnitTest
{		
	TEST_CLASS(CmdDeleteItemTest)
	{
	public:

		TEST_METHOD(CmdDeleteItem_SingleDeletionTest)
		{
			ItemBank* itemBank = new ItemBank();
			Item* task = new Item();
			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(static_cast<OutputControl::CurrentScreenType>(0));

			itemBank->addToBank(task);
			Assert::AreEqual(itemBank->getBankSize(), 1);

			vector<Item*>itemsToBeDeleted;
			itemsToBeDeleted.push_back(task);

			CmdDeleteItem* cmdDeleteItem = new CmdDeleteItem(itemsToBeDeleted);
			cmdDeleteItem->deleteItemsFromBank();
			Assert::AreEqual(itemBank->getBankSize(), 0);

			itemBank->clearBank();
		}

		TEST_METHOD(CmdDeleteItem_MultipleDeletionTest)
		{
			ItemBank* itemBank = new ItemBank();
			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(static_cast<OutputControl::CurrentScreenType>(0));

			Item* task1 = new Item();
			itemBank->addToBank(task1);
			Assert::AreEqual(itemBank->getBankSize(), 1);

			Item* task2 = new Item();
			itemBank->addToBank(task2);
			Assert::AreEqual(itemBank->getBankSize(), 2);

			Item* task3 = new Item();
			itemBank->addToBank(task3);
			Assert::AreEqual(itemBank->getBankSize(), 3);

			vector<Item*>itemsToBeDeleted;
			itemsToBeDeleted.push_back(task1);
			itemsToBeDeleted.push_back(task2);

			CmdDeleteItem* cmdDeleteItem = new CmdDeleteItem(itemsToBeDeleted);
			cmdDeleteItem->deleteItemsFromBank();
			Assert::AreEqual(itemBank->getBankSize(), 1);

			itemBank->clearBank();
		}

		TEST_METHOD(CmdDeleteItem_DeleteAllTest)
		{
			ItemBank* itemBank = new ItemBank();
			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(static_cast<OutputControl::CurrentScreenType>(0));

			Item* task1 = new Item();
			itemBank->addToBank(task1);
			Assert::AreEqual(itemBank->getBankSize(), 1);

			Item* task2 = new Item();
			itemBank->addToBank(task2);
			Assert::AreEqual(itemBank->getBankSize(), 2);

			Item* task3 = new Item();
			itemBank->addToBank(task3);
			Assert::AreEqual(itemBank->getBankSize(), 3);

			vector<Item*>itemsToBeDeleted;
			itemsToBeDeleted.push_back(task1);
			itemsToBeDeleted.push_back(task2);
			itemsToBeDeleted.push_back(task3);

			CmdDeleteItem* cmdDeleteItem = new CmdDeleteItem(itemsToBeDeleted);
			cmdDeleteItem->deleteItemsFromBank();
			Assert::AreEqual(itemBank->getBankSize(), 0);

			itemBank->clearBank();
		}
	};
}