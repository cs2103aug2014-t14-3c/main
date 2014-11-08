//@author A0116781A
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string source = "../UnitTestLeon/TestItems.txt";
const string destination = "JustAddIt/JustAddIt_ItemBank.txt";
const string FILL = "Filler text to test code";
const string DATE = "Saturday 15 Nov 2014 08:00AM";
const string PRIORITY_HIGH = "High";

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
		TEST_METHOD(addToBank_Neg) 
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

		// adding 2 duplicate items to empty bank shows conflict with other items
		TEST_METHOD(addToBank_Pos) 
		{
			itemBank->clearBank();

			Item* itemPtr1 = new Item;
			itemPtr1->setTitle(FILL);
			itemPtr1->setDescription(FILL);
			itemPtr1->setVenue(FILL);
			itemPtr1->setCategory(FILL);
			itemPtr1->setStartDate(15, 10);
			itemPtr1->setStartTime(8, 0);
			itemPtr1->setEndDate(15, 10);
			itemPtr1->setEndTime(8, 0);

			Item* itemPtr2 = new Item;
			*itemPtr2 = *itemPtr1;

			Assert::IsFalse(itemBank->addToBank(itemPtr1));
			Assert::IsTrue(itemBank->addToBank(itemPtr2));
			Assert::AreEqual(itemBank->getBankSize(), 2);
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

			itemBank->resetBank();

			Assert::AreEqual(15, itemBank->getBankSize());
			Assert::AreEqual(2, (int)itemBank->getAllDeadlines().size());
			Assert::AreEqual(5, (int)itemBank->getAllEvents().size());
			Assert::AreEqual(8, (int)itemBank->getAllTasks().size());
		}
				
		// reset bank to initial loaded bank
		TEST_METHOD(deleteItems) 
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

			itemBank->resetBank();

			Assert::AreEqual(15, itemBank->getBankSize());
			Assert::AreEqual(2, (int)itemBank->getAllDeadlines().size());
			Assert::AreEqual(5, (int)itemBank->getAllEvents().size());
			Assert::AreEqual(8, (int)itemBank->getAllTasks().size());
		}
	};
}