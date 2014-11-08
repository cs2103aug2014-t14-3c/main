#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(ParserTest)
	{
	public:
		
		TEST_METHOD(TestExecutor)
		{
			Executor* myExec = new Executor();
			ItemBank* myIB = ItemBank::getInstance();
			DisplayScreenConstructor* myDSC = DisplayScreenConstructor::getInstance();
			OutputControl* myOC = new OutputControl();

			myExec->execute("add wake up on 30 Dec at 7 #category (more info)");

		
			Assert::AreEqual("wake up", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Tuesday 30 Dec 2014 07:00AM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			Assert::AreEqual("Tuesday 30 Dec 2014 08:00AM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			Assert::AreEqual("category", OutputControl::getItemAddr(1)->getCategory().c_str());
			Assert::AreEqual("more info", OutputControl::getItemAddr(1)->getDescription().c_str());
			Assert::AreEqual("Low", OutputControl::getItemAddr(1)->getPriorityInString().c_str());
		
			try{
				myExec->execute("add more info(");
			}
			catch (exception& e){
				Assert::AreEqual("Invalid brackets! Please follow e.g. add event at 7pm (description)", e.what() );
			}

			myIB->clearBank();
		}
	};
}