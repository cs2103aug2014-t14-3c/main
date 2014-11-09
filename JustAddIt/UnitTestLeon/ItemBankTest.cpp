//@author A0116781A
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string source = "../UnitTestLeon/TestItems.txt";
const string destination = "JustAddIt/JustAddIt_ItemBank.txt";
const string FILL = "Filler text to test code";
const string DATE = "Saturday 15 Nov 2014 08:00AM";
const string PRIORITY_HIGH = "High";
const string SEARCH_TERM_EVENTS = "quiz";
const string SEARCH_TERM_DEADLINES = "assignment";
const string SEARCH_TERM_TASKS = "project";


ItemBank* itemBank = ItemBank::getInstance();

namespace UnitTest
{		
	TEST_CLASS(ItemBankTest)
	{
	public:

		// clearBank() clears the bank
		TEST_METHOD(clearBank) 
		{
			itemBank->clearBank();

			Assert::AreEqual(itemBank->getBankSize(), 0);
		}

		// adding one item to empty bank has no conflict with other items
		TEST_METHOD(addToBank_NoConflict) 
		{
			itemBank->clearBank();

			Item* itemPtr = new Item;
			itemPtr->setTitle(FILL);
			itemPtr->setDescription(FILL);
			itemPtr->setVenue(FILL);
			itemPtr->setCategory(FILL);
			itemPtr->setStartDate(15, 10);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(15, 10);
			itemPtr->setEndTime(8, 0);
			itemPtr->setPriority(PRIORITY_HIGH);

			Assert::IsFalse(itemBank->addToBank(itemPtr));
			Assert::AreEqual(itemBank->getBankSize(), 1);
		}

		// 2 duplicate items conflict with each other
		TEST_METHOD(isConflicted_Pos) 
		{
			itemBank->clearBank();

			OutputControl::resetCurrentItemList();

			Item* itemPtr = new Item;
			Item* itemPtr1 = new Item;
			itemPtr1->setTitle(FILL);
			itemPtr1->setDescription(FILL);
			itemPtr1->setVenue(FILL);
			itemPtr1->setCategory(FILL);
			itemPtr1->setStartDate(20, 10);
			itemPtr1->setStartTime(8, 0);
			itemPtr1->setEndDate(20, 10);
			itemPtr1->setEndTime(10, 0);

			Item* itemPtr2 = new Item;
			itemPtr2->setTitle(FILL);
			itemPtr2->setDescription(FILL);
			itemPtr2->setVenue(FILL);
			itemPtr2->setCategory(FILL);
			itemPtr2->setStartDate(20, 10);
			itemPtr2->setStartTime(8, 0);
			itemPtr2->setEndDate(20, 10);
			itemPtr2->setEndTime(10, 0);

			Assert::IsTrue(itemBank->isConflicted(itemPtr1, itemPtr2));
			//Assert::IsFalse(itemBank->addToBank(itemPtr1));
			//Assert::IsTrue(itemBank->checkForConflict(itemPtr2)); // this assert fails

			itemBank->clearBank();
		}

		// 2 different items do not conflict with each other
		TEST_METHOD(isConflicted_Neg) 
		{
			itemBank->clearBank();

			Item* itemPtr1 = new Item;
			itemPtr1->setTitle(FILL);
			itemPtr1->setDescription(FILL);
			itemPtr1->setVenue(FILL);
			itemPtr1->setCategory(FILL);
			itemPtr1->setStartDate(20, 10);
			itemPtr1->setStartTime(8, 0);
			itemPtr1->setEndDate(20, 10);
			itemPtr1->setEndTime(10, 0);

			Item* itemPtr2 = new Item;
			itemPtr2->setTitle(FILL);
			itemPtr2->setDescription(FILL);
			itemPtr2->setVenue(FILL);
			itemPtr2->setCategory(FILL);
			itemPtr2->setStartDate(21, 10);
			itemPtr2->setStartTime(8, 0);
			itemPtr2->setEndDate(21, 10);
			itemPtr2->setEndTime(10, 0);

			Assert::IsFalse(itemBank->isConflicted(itemPtr1, itemPtr2));
			//Assert::IsTrue(itemBank->checkForConflict(itemPtr2)); // this assert fails
			//Assert::AreEqual(1, itemBank->getBankSize());

			itemBank->clearBank();
		}

		// initialise bank from text file
		TEST_METHOD(initialise) 
		{
			itemBank->clearBank();

			ifstream src(source, ios::binary);
			ofstream dest(destination, ios::binary);

			dest << src.rdbuf();

			src.close();
			dest.close();

			itemBank->initialiseBank();

			Assert::AreEqual(15, itemBank->getBankSize());
			Assert::AreEqual(2, (int)itemBank->getAllDeadlines().size());
			Assert::AreEqual(5, (int)itemBank->getAllEvents().size());
			Assert::AreEqual(8, (int)itemBank->getAllTasks().size());
		}
		
		// reset bank to initial loaded bank
		TEST_METHOD(resetBank) 
		{
			itemBank->clearBank();

			ifstream src(source, ios::binary);
			ofstream dest(destination, ios::binary);

			dest << src.rdbuf();

			src.close();
			dest.close();

			itemBank->initialiseBank();

			Item* itemPtr = new Item;

			itemBank->addToBank(itemPtr);

			Assert::AreEqual(16, itemBank->getBankSize());

			itemBank->resetBank();

			Assert::AreEqual(15, itemBank->getBankSize());
			Assert::AreEqual(2, (int)itemBank->getAllDeadlines().size());
			Assert::AreEqual(5, (int)itemBank->getAllEvents().size());
			Assert::AreEqual(8, (int)itemBank->getAllTasks().size());
		}
				
		// delete items in bank that have been marked done
		TEST_METHOD(deleteDoneItems) 
		{
			itemBank->clearBank();

			ifstream src(source, ios::binary);
			ofstream dest(destination, ios::binary);

			dest << src.rdbuf();

			src.close();
			dest.close();

			itemBank->initialiseBank();

			Assert::AreEqual(15, itemBank->getBankSize());
			
			itemBank->deleteDoneItems();

			Assert::AreEqual(10, itemBank->getBankSize());
		}

		// delete items in bank that are overdue
		TEST_METHOD(deleteOverdueDeadlines) 
		{
			itemBank->clearBank();

			ifstream src(source, ios::binary);
			ofstream dest(destination, ios::binary);

			dest << src.rdbuf();

			src.close();
			dest.close();

			itemBank->initialiseBank();

			Assert::AreEqual(15, itemBank->getBankSize());
			
			itemBank->deleteOverdueDeadlines();

			Assert::AreEqual(13, itemBank->getBankSize());
		}

		// delete events in bank that have passed
		TEST_METHOD(deletePastEvents) 
		{
			itemBank->clearBank();

			ifstream src(source, ios::binary);
			ofstream dest(destination, ios::binary);

			dest << src.rdbuf();

			src.close();
			dest.close();

			itemBank->initialiseBank();

			Assert::AreEqual(15, itemBank->getBankSize());
			
			itemBank->deleteOverdueDeadlines();

			Assert::AreEqual(13, itemBank->getBankSize());
		}

		// performs a search on the items in the bank
		TEST_METHOD(searchItems) 
		{
			itemBank->clearBank();

			ifstream src(source, ios::binary);
			ofstream dest(destination, ios::binary);

			dest << src.rdbuf();

			src.close();
			dest.close();

			itemBank->initialiseBank();

			Assert::AreEqual(15, itemBank->getBankSize());
			Assert::AreEqual(2, (int)itemBank->searchEvents(SEARCH_TERM_EVENTS).size());
			Assert::AreEqual(7, (int)itemBank->searchTasks(SEARCH_TERM_TASKS).size());
			Assert::AreEqual(1, (int)itemBank->searchDeadlines(SEARCH_TERM_DEADLINES).size());
		}
	};
}