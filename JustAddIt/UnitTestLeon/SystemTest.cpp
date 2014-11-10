//@author A0110770U
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(SystemTest)
	{
	public:

		TEST_METHOD(SystemTest_EmptyItemBank)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			ActionLog::resetLog();
			OutputControl::resetCurrentItemList();
			myIB->clearBank();
			myExec->execute("home");
			Assert::AreEqual(0, OutputControl::getNumberOfDisplayedItems());
			myExec->execute("t");
			Assert::AreEqual(0, OutputControl::getNumberOfDisplayedItems());
			myExec->execute("home");
			myExec->execute("o");
			Assert::AreEqual(0, OutputControl::getNumberOfDisplayedItems());
			myExec->execute("search sth");
			Assert::AreEqual(0, OutputControl::getNumberOfDisplayedItems());
		}
			TEST_METHOD(SystemTest_ListAndEditScenarios)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			OutputControl::resetCurrentItemList();
			myIB->clearBank();
			myExec->execute("add event on 30 Dec at 7 #category (more info)");		
			myExec->execute("add deadline by 28 December !!");
			myExec->execute("add floating task");
			myExec->execute("home");
			myExec->execute("t");
			Assert::AreEqual(3, OutputControl::getNumberOfDisplayedItems());	

			myExec->execute("e 1");
			Assert::AreEqual("event", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Tuesday 30 Dec 2014 07:00AM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			myExec->execute("o");

			myExec->execute("e 2");
			Assert::AreEqual("deadline", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Sunday 28 Dec 2014 11:59PM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			myExec->execute("o");

			myExec->execute("e 3");
			Assert::AreEqual("floating task", OutputControl::getItemAddr(1)->getTitle().c_str());
			myExec->execute("o");

			
		}
		TEST_METHOD(SystemTest_SearchAndEditScenarios)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			OutputControl::resetCurrentItemList();
			myIB->clearBank();

			myExec->execute("add wake up on 30 Dec at 7 #category (more info)");
			myExec->execute("add dinner on 30 Nov at 8 #personal (bring cash)");
			myExec->execute("add expensive dinner on 25 Dec 2300");
				
			myExec->execute("search wake");
			Assert::AreEqual(1, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("wake up", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Tuesday 30 Dec 2014 07:00AM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			Assert::AreEqual("Tuesday 30 Dec 2014 08:00AM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			Assert::AreEqual("category", OutputControl::getItemAddr(1)->getCategory().c_str());
			Assert::AreEqual("more info", OutputControl::getItemAddr(1)->getDescription().c_str());
			Assert::AreEqual("Low", OutputControl::getItemAddr(1)->getPriorityInString().c_str());
			
			myExec->execute("search dinner");
			Assert::AreEqual(2, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("dinner", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Sunday 30 Nov 2014 08:00AM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			Assert::AreEqual("Sunday 30 Nov 2014 09:00AM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			Assert::AreEqual("personal", OutputControl::getItemAddr(1)->getCategory().c_str());
			Assert::AreEqual("bring cash", OutputControl::getItemAddr(1)->getDescription().c_str());
			Assert::AreEqual("Low", OutputControl::getItemAddr(1)->getPriorityInString().c_str());
			
			myExec->execute("e 1");
			myExec->execute("e 1 new title");
			myExec->execute("o");

			Assert::AreEqual(1, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("expensive dinner", OutputControl::getItemAddr(1)->getTitle().c_str());

			myExec->execute("search cash");
			Assert::AreEqual(OutputControl::getNumberOfDisplayedItems(), 1);
			Assert::AreEqual("new title", OutputControl::getItemAddr(1)->getTitle().c_str());
			
			myExec->execute("e 1");
			myExec->execute("e 2 bring money");
			myExec->execute("o");
			Assert::AreEqual(0, OutputControl::getNumberOfDisplayedItems());
			
		}
		TEST_METHOD(SystemTest_AddEditFields)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			OutputControl::resetCurrentItemList();
			myIB->clearBank();

			myExec->execute("add concert on 30 Dec at 7 #category (more info)");		
			myExec->execute("e 1 new title");
			Assert::AreEqual(1, OutputControl::getNumberOfDisplayedItems());;
			Assert::AreEqual("new title", OutputControl::getItemAddr(1)->getTitle().c_str());

			myExec->execute("e 2 new description");
			Assert::AreEqual("new description", OutputControl::getItemAddr(1)->getDescription().c_str());

			myExec->execute("e 3 25 dec 2pm");
			Assert::AreEqual("Thursday 25 Dec 2014 02:00PM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			
			myExec->execute("e 4 26 dec 4pm");
			Assert::AreEqual("Friday 26 Dec 2014 04:00PM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			
			myExec->execute("e 5 high");
			Assert::AreEqual("High", OutputControl::getItemAddr(1)->getPriorityInString().c_str());

			myExec->execute("e 6 new cat");
			Assert::AreEqual("new cat", OutputControl::getItemAddr(1)->getCategory().c_str());
		
				
		}
	
		TEST_METHOD(SystemTest_MarkAndClearDoneScenarios)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			ActionLog::resetLog();
			OutputControl::resetCurrentItemList();
			myIB->clearBank();
			myExec->execute("add event on 30 Dec at 7 #category (more info)");		
			myExec->execute("add deadline by 28 December !!");
			myExec->execute("add floating task");
			myExec->execute("home");
			myExec->execute("t");
			Assert::AreEqual(3, OutputControl::getNumberOfDisplayedItems());
		
			myExec->execute("e 1");
			Assert::AreEqual("event", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Tuesday 30 Dec 2014 07:00AM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			myExec->execute("o");

			myExec->execute("e 2");
			Assert::AreEqual("deadline", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Sunday 28 Dec 2014 11:59PM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			myExec->execute("o");

			myExec->execute("e 3");
			Assert::AreEqual("floating task", OutputControl::getItemAddr(1)->getTitle().c_str());
			myExec->execute("o");

			myExec->execute("m 1 3");
			Assert::IsTrue(OutputControl::getItemAddr(1)->isDone());
			Assert::IsFalse(OutputControl::getItemAddr(2)->isDone());
			Assert::IsTrue(OutputControl::getItemAddr(3)->isDone());

			myExec->execute("m 3");
			Assert::IsTrue(OutputControl::getItemAddr(1)->isDone());
			Assert::IsFalse(OutputControl::getItemAddr(2)->isDone());
			Assert::IsFalse(OutputControl::getItemAddr(3)->isDone());
			
			myExec->execute("c");
			Assert::AreEqual("deadline", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("floating task", OutputControl::getItemAddr(2)->getTitle().c_str());
			
			
			myExec->execute("undo");
			Assert::AreEqual("event", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("deadline", OutputControl::getItemAddr(2)->getTitle().c_str());
			Assert::AreEqual("floating task", OutputControl::getItemAddr(3)->getTitle().c_str());
		}
		TEST_METHOD(SystemTest_DeleteScenarios)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			ActionLog::resetLog();
			OutputControl::resetCurrentItemList();
			myIB->clearBank();
			myExec->execute("add eoy party on 30 Dec at 7 #category (more info)");
			myExec->execute("add eoy dinner on 29 Dec at 8");
			myExec->execute("add tutorial by 28 December !");
			myExec->execute("add floaters");
			myExec->execute("home");
			myExec->execute("t");
			Assert::AreEqual(4, OutputControl::getNumberOfDisplayedItems());
			//deleting in list view
			myExec->execute("d 1 3");
			Assert::AreEqual(2, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("eoy dinner", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("floaters", OutputControl::getItemAddr(2)->getTitle().c_str());
			//undoing delete
			myExec->execute("undo");
			Assert::AreEqual(4, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("eoy party", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("eoy dinner", OutputControl::getItemAddr(2)->getTitle().c_str());
			Assert::AreEqual("tutorial", OutputControl::getItemAddr(3)->getTitle().c_str());
			Assert::AreEqual("floaters", OutputControl::getItemAddr(4)->getTitle().c_str());
			//deleting in edit screen
			myExec->execute("e 4");
			myExec->execute("d");
			Assert::AreEqual(3, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("eoy party", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("eoy dinner", OutputControl::getItemAddr(2)->getTitle().c_str());
			Assert::AreEqual("tutorial", OutputControl::getItemAddr(3)->getTitle().c_str());
			//deleting in search screen
			myExec->execute("search eoy");
			Assert::AreEqual(2, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("eoy party", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("eoy dinner", OutputControl::getItemAddr(2)->getTitle().c_str());
			myExec->execute("d 1");
			Assert::AreEqual(1, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("eoy dinner", OutputControl::getItemAddr(1)->getTitle().c_str());
			OutputControl::resetCurrentItemList();
			myIB->clearBank();
		}
		TEST_METHOD(SystemTest_NegExceptions)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			ActionLog::resetLog();
			OutputControl::resetCurrentItemList();
			myIB->clearBank();
			myExec->execute("home");
			try{
				myExec->execute("rubbish");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_INVALID_COMMAND.c_str(), e.what());
			};
			try{
				myExec->execute("add on Saturday");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_MISSING_TITLE.c_str(), e.what());
			};
			try{
				myExec->execute("add event at 2pm )description");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_INVALID_BRACKETS.c_str(), e.what());
			};
			try{
				myExec->execute("add event # category");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_MISSING_CATEGORY.c_str(), e.what());
			};
			myExec->execute("add birthday at 2pm");
			myExec->execute("add assignemnt due 6pm !!");
			myExec->execute("add cloud");
			myExec->execute("o");
			myExec->execute("t");
			
			try{
				myExec->execute("e 4");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_INVALID_ITEM_NO.c_str(), e.what());
			};
			myExec->execute("e 1");
			try{
				myExec->execute("e 7");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_INVALID_FIELD_NO.c_str(), e.what());
			};
			try{
				myExec->execute("e 5 whatever");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_INVALID_PRIORITY.c_str(), e.what());
			};
			try{
				myExec->execute("e 3 10pm");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_LOGIC_START_END.c_str(), e.what());
			};
			try{
				myExec->execute("e 4 1pm");
			}
			catch(exception& e){
				Assert::AreEqual(Parser::ERROR_LOGIC_START_END.c_str(), e.what());
			};
		}	
		TEST_METHOD(SystemTest_OverdueScenarios)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			myIB->clearBank();
			ActionLog::resetLog();
			OutputControl::resetCurrentItemList();
			//add two overdue items for testing
			Item* overdueItemA = new Item;
			tm yesterdayTM;
			time_t currentTime;
			time(&currentTime);
			localtime_s(&yesterdayTM, &currentTime);
			yesterdayTM.tm_mday--;
			mktime(&yesterdayTM);

			overdueItemA -> setItemType("deadline");
			overdueItemA -> setTitle("urgent job");
			overdueItemA -> setEndDateTime(yesterdayTM);
			myIB->addToBank(overdueItemA);

			Item* overdueItemB = new Item;
			yesterdayTM.tm_mday--;
			mktime(&yesterdayTM);
			overdueItemB -> setItemType("deadline");
			overdueItemB -> setTitle("urgent task");
			overdueItemB -> setEndDateTime(yesterdayTM);
			myIB->addToBank(overdueItemB);
			//add new items
			myExec->execute("add some event on 20 nov");
			myExec->execute("add random task");
			myExec->execute("add new deadline due 25 dec");
			
			myExec->execute("home");
			myExec->execute("t");
			Assert::AreEqual(5, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("some event", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("urgent job", OutputControl::getItemAddr(2)->getTitle().c_str());
			Assert::AreEqual("urgent task", OutputControl::getItemAddr(3)->getTitle().c_str());
			Assert::AreEqual("new deadline", OutputControl::getItemAddr(4)->getTitle().c_str());
			Assert::AreEqual("random task", OutputControl::getItemAddr(5)->getTitle().c_str());

			//deleting and marking in overdue screen
			myExec->execute("home");
			myExec->execute("o");
			myExec->execute("m 2");
			Assert::AreEqual("urgent job", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("urgent task", OutputControl::getItemAddr(2)->getTitle().c_str());
			Assert::AreEqual(false, OutputControl::getItemAddr(1)->isDone());
			Assert::AreEqual(true, OutputControl::getItemAddr(2)->isDone());
			myExec->execute("d 1");
			Assert::AreEqual(1, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("urgent task", OutputControl::getItemAddr(1)->getTitle().c_str());

			myExec->execute("home");
			myExec->execute("o");
			myExec->execute("c");
			myExec->execute("home");
			myExec->execute("t");
			Assert::AreEqual(3, OutputControl::getNumberOfDisplayedItems());
			Assert::AreEqual("some event", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("new deadline", OutputControl::getItemAddr(2)->getTitle().c_str());
			Assert::AreEqual("random task", OutputControl::getItemAddr(3)->getTitle().c_str());
			
			

		}

	};
}