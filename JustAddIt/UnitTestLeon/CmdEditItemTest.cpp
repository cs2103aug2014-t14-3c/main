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
	TEST_CLASS(CmdEditItemTest)
	{
	public:

		TEST_METHOD(CmdEditItem_EditTitleTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();

			Item* itemPtr = new Item;
			itemPtr->setTitle("Title");
			itemPtr->setDescription("Description");
			itemPtr->setVenue("-");
			itemPtr->setCategory("Category");
			itemPtr->setPriority(static_cast<Item::PriorityLevel>(1));
			itemPtr->setStartDate(23, 9);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(23, 9);
			itemPtr->setEndTime(8, 0);
			itemPtr->setItemTypeTask();

			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(static_cast<OutputControl::CurrentScreenType>(0));

			itemBank->addToBank(itemPtr);
			Assert::AreEqual(itemBank->getBankSize(), 1);
			CmdEditItem* cmdEditItem = new CmdEditItem(itemBank->findIter(itemPtr), 1, "New Title");
			cmdEditItem->execute();
			Assert::AreEqual((*itemBank->findIter(itemPtr))->getTitle().c_str(), "New Title");
			itemBank->clearBank();
		}

		TEST_METHOD(CmdEditItem_EditDescriptionTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();

			Item* itemPtr = new Item;
			itemPtr->setTitle("Title");
			itemPtr->setDescription("Description");
			itemPtr->setVenue("-");
			itemPtr->setCategory("Category");
			itemPtr->setPriority(static_cast<Item::PriorityLevel>(1));
			itemPtr->setStartDate(23, 9);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(23, 9);
			itemPtr->setEndTime(8, 0);
			itemPtr->setItemTypeTask();

			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(static_cast<OutputControl::CurrentScreenType>(0));

			itemBank->addToBank(itemPtr);
			Assert::AreEqual(itemBank->getBankSize(), 1);
			CmdEditItem* cmdEditItem = new CmdEditItem(itemBank->findIter(itemPtr), 2, "New Description");
			cmdEditItem->execute();
			Assert::AreEqual((*itemBank->findIter(itemPtr))->getDescription().c_str(), "New Description");
			itemBank->clearBank();
		}

		TEST_METHOD(CmdEditItem_EditStartTimeTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();

			Item* itemPtr = new Item;

			time_t currentTime_timet;
			tm currentTime_struct;
			time(&currentTime_timet);
			localtime_s(&currentTime_struct, &currentTime_timet);

			Item* newItemPtr = new Item();
			newItemPtr->setStartDateTime(currentTime_struct);

			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(static_cast<OutputControl::CurrentScreenType>(0));

			itemBank->addToBank(itemPtr);
			Assert::AreEqual(itemBank->getBankSize(), 1);
			CmdEditItem* cmdEditItem = new CmdEditItem(itemBank->findIter(itemPtr), 3, currentTime_struct);
			cmdEditItem->execute();
			itemBank->editItemStartDateTime(itemPtr, currentTime_struct);
			Assert::AreEqual((*itemBank->findIter(itemPtr))->getStartDateInString().c_str(), newItemPtr->getStartDateInString().c_str());
			itemBank->clearBank();
		}
		TEST_METHOD(CmdEditItem_EditEndTimeTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();

			Item* itemPtr = new Item;

			time_t currentTime_timet;
			tm currentTime_struct;
			time(&currentTime_timet);
			localtime_s(&currentTime_struct, &currentTime_timet);

			Item* newItemPtr = new Item();
			newItemPtr->setEndDateTime(currentTime_struct);

			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(static_cast<OutputControl::CurrentScreenType>(0));

			itemBank->addToBank(itemPtr);
			Assert::AreEqual(itemBank->getBankSize(), 1);
			CmdEditItem* cmdEditItem = new CmdEditItem(itemBank->findIter(itemPtr), 3, currentTime_struct);
			cmdEditItem->execute();
			itemBank->editItemEndDateTime(itemPtr, currentTime_struct);
			Assert::AreEqual((*itemBank->findIter(itemPtr))->getEndDateInString().c_str(), newItemPtr->getEndDateInString().c_str());
			itemBank->clearBank();
		}
		TEST_METHOD(CmdEditItem_EditPriorityTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();

			Item* itemPtr = new Item;
			itemPtr->setTitle("Title");
			itemPtr->setDescription("Description");
			itemPtr->setVenue("-");
			itemPtr->setCategory("Category");
			itemPtr->setPriority(static_cast<Item::PriorityLevel>(1));
			itemPtr->setStartDate(23, 9);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(23, 9);
			itemPtr->setEndTime(8, 0);
			itemPtr->setItemTypeTask();

			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(static_cast<OutputControl::CurrentScreenType>(0));

			itemBank->addToBank(itemPtr);
			Assert::AreEqual(itemBank->getBankSize(), 1);
			CmdEditItem* cmdEditItem = new CmdEditItem(itemBank->findIter(itemPtr), 5, static_cast<Item::PriorityLevel>(2));
			cmdEditItem->execute();
			Assert::AreEqual((*itemBank->findIter(itemPtr))->getPriorityInString().c_str(), "High");
			itemBank->clearBank();
		}
		TEST_METHOD(CmdEditItem_EditCategoryTest)
		{
			ItemBank* itemBank = ItemBank::getInstance();
			itemBank->clearBank();

			Item* itemPtr = new Item;
			itemPtr->setTitle("Title");
			itemPtr->setDescription("Description");
			itemPtr->setVenue("-");
			itemPtr->setCategory("Category");
			itemPtr->setPriority(Item::PriorityLevel::MED);
			itemPtr->setStartDate(23, 9);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(23, 9);
			itemPtr->setEndTime(8, 0);
			itemPtr->setItemTypeTask();

			OutputControl* outputControl = new OutputControl();
			outputControl->setCurrentScreen(OutputControl::CurrentScreenType::HOME_SCREEN);

			itemBank->addToBank(itemPtr);
			Assert::AreEqual(itemBank->getBankSize(), 1);
			CmdEditItem* cmdEditItem = new CmdEditItem(itemBank->findIter(itemPtr), 6, "New Category");
			cmdEditItem->execute();
			Assert::AreEqual((*itemBank->findIter(itemPtr))->getCategory().c_str(), "New Category");
			itemBank->clearBank();
		}
	};
}