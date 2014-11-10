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
	TEST_CLASS(CmdMarkItemDoneTest)
	{
	public:

		TEST_METHOD(CmdMarkItemDone_SingleMarkTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();
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

			vector<Item*>itemsToBeMarked;
			itemsToBeMarked.push_back(task1);

			CmdMarkItemDone* cmdMarkItemDone = new CmdMarkItemDone(itemsToBeMarked);
			cmdMarkItemDone->execute();
			Assert::AreEqual(itemBank->getNumberOfMarkedItems(), 1);

			itemBank->clearBank();
		}

		TEST_METHOD(CmdMarkItemDone_MultipleMarkTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();
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

			vector<Item*>itemsToBeMarked;
			itemsToBeMarked.push_back(task1);
			itemsToBeMarked.push_back(task2);

			CmdMarkItemDone* cmdMarkItemDone = new CmdMarkItemDone(itemsToBeMarked);
			cmdMarkItemDone->execute();
			Assert::AreEqual(itemBank->getNumberOfMarkedItems(), 2);

			itemBank->clearBank();
		}

		TEST_METHOD(CmdMarkItemDone_MarkAllTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();
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

			vector<Item*>itemsToBeMarked;
			itemsToBeMarked.push_back(task1);
			itemsToBeMarked.push_back(task2);
			itemsToBeMarked.push_back(task3);

			CmdMarkItemDone* cmdMarkItemDone = new CmdMarkItemDone(itemsToBeMarked);
			cmdMarkItemDone->execute();
			Assert::AreEqual(itemBank->getNumberOfMarkedItems(), 3);

			itemBank->clearBank();
		}
	};
}