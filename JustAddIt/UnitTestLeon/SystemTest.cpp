#include "stdafx.h"
#include "CppUnitTest.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(SystemTest)
	{
	public:
		
		TEST_METHOD(SystemTest_AddSearch)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			

			myExec->execute("add wake up on 30 Dec at 7 #category (more info)");
			myExec->execute("add dinner on 30 Nov at 8 #personal (bring cash)");
			myExec->execute("add expensive dinner on 25 Dec 2300");
				
			myExec->execute("search wake");
			Assert::AreEqual(OutputControl::getNumberOfDisplayedItems(), 1);
			Assert::AreEqual("wake up", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Tuesday 30 Dec 2014 07:00AM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			Assert::AreEqual("Tuesday 30 Dec 2014 08:00AM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			Assert::AreEqual("category", OutputControl::getItemAddr(1)->getCategory().c_str());
			Assert::AreEqual("more info", OutputControl::getItemAddr(1)->getDescription().c_str());
			Assert::AreEqual("Low", OutputControl::getItemAddr(1)->getPriorityInString().c_str());
			
			myExec->execute("search dinner");
			Assert::AreEqual(OutputControl::getNumberOfDisplayedItems(), 2);
			Assert::AreEqual("dinner", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Sunday 30 Nov 2014 08:00AM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			Assert::AreEqual("Sunday 30 Nov 2014 09:00AM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			Assert::AreEqual("personal", OutputControl::getItemAddr(1)->getCategory().c_str());
			Assert::AreEqual("bring cash", OutputControl::getItemAddr(1)->getDescription().c_str());
			Assert::AreEqual("Low", OutputControl::getItemAddr(1)->getPriorityInString().c_str());
			
			
			
			
			myIB->clearBank();
		}
		TEST_METHOD(SystemTest_AddEditFields)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			

			myExec->execute("add concert on 30 Dec at 7 #category (more info)");		
			myExec->execute("e 1 new title");
			Assert::AreEqual(OutputControl::getNumberOfDisplayedItems(), 1);
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
		
				
			
			myIB->clearBank();
		}
		TEST_METHOD(SystemTest_ListEditItems)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			

			myExec->execute("add event on 30 Dec at 7 #category (more info)");		
			myExec->execute("add deadline by 28 December !!");
			myExec->execute("add floating task");
			myExec->execute("o");
			myExec->execute("t");
			Assert::AreEqual(OutputControl::getNumberOfDisplayedItems(), 3);
		
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
			
				
			
			myIB->clearBank();
		}
		TEST_METHOD(SystemTest_MarkAndClearScenario)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			

			myExec->execute("add event on 30 Dec at 7 #category (more info)");		
			myExec->execute("add deadline by 28 December !!");
			myExec->execute("add floating task");
			myExec->execute("o");
			myExec->execute("t");
			Assert::AreEqual(OutputControl::getNumberOfDisplayedItems(), 3);
		
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
			Assert::AreEqual(true, OutputControl::getItemAddr(1)->isDone());
			Assert::AreEqual(false, OutputControl::getItemAddr(2)->isDone());
			Assert::AreEqual(false, OutputControl::getItemAddr(3)->isDone());

			//myExec->execute("undo");
			//Assert::IsTrue(OutputControl::getItemAddr(1)->isDone());
			//Assert::IsFalse(OutputControl::getItemAddr(2)->isDone());
			//Assert::IsTrue(OutputControl::getItemAddr(3)->isDone());

			myIB->clearBank();
		}
		TEST_METHOD(SystemTest_NegExceptions)
		{
					/*
			try{
				myExec->execute("add more info(");
			}
			catch (exception& e){
				Assert::AreEqual("Invalid brackets! Please follow e.g. add event at 7pm (description)", e.what() );
			}
			*/
		}
	
	};
}