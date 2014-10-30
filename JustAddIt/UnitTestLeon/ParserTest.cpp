#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLeon
{		
	TEST_CLASS(ParserTest)
	{
	public:
		
		TEST_METHOD(TestStringToHourInt)
		{
			Parser myParser;
			Assert::AreEqual(17, myParser.convertStringToIntHour("5pm"));
			Assert::AreEqual(21, myParser.convertStringToIntHour("9PM"));
			Assert::AreEqual(0, myParser.convertStringToIntHour("12"));
			Assert::AreEqual(11, myParser.convertStringToIntHour("11am"));
			Assert::AreEqual(1, myParser.convertStringToIntHour("1AM"));
			Assert::AreEqual(22, myParser.convertStringToIntHour("2204"));
			Assert::AreEqual(0, myParser.convertStringToIntHour("12am"));
			Assert::AreEqual(12, myParser.convertStringToIntHour("12pm"));
		}

		TEST_METHOD(TestStringToMinInt)
		{
			Parser myParser;
			Assert::AreEqual(30, myParser.convertStringToIntMin("5.30pm"));
			Assert::AreEqual(50, myParser.convertStringToIntMin("7:50am"));
			Assert::AreEqual(59, myParser.convertStringToIntMin("2.59"));
			Assert::AreEqual(0, myParser.convertStringToIntMin("5:00"));
			Assert::AreEqual(0, myParser.convertStringToIntMin("5:00"));
		}

		TEST_METHOD(TestEmbedTitle)
		{
			Parser myParser;
			Item* myItem = new Item;
			string expectedString = "dinner reserve";
			string testString = "dinner reserve at 8pm on 3 Sep";
			myParser.detectTitleAndEmbed(myItem, testString);
			Assert::AreEqual(expectedString, myItem->getTitle());

			testString = "dinner reserve on 3 Sep at 8pm";
			myParser.detectTitleAndEmbed(myItem, testString);
			Assert::AreEqual(expectedString, myItem->getTitle());

			expectedString = "lunch";
			testString = "lunch on 3 Sep at 8pm";
			myParser.detectTitleAndEmbed(myItem, testString);
			Assert::AreEqual(expectedString, myItem->getTitle());

			expectedString = "deadline two three";
			testString = "deadline two three by 8pm";
			myParser.detectTitleAndEmbed(myItem, testString);
			Assert::AreEqual(expectedString, myItem->getTitle());

			expectedString = "event one";
			testString = "event one 2pm to 3pm";
			myParser.detectTitleAndEmbed(myItem, testString);
			Assert::AreEqual(expectedString, myItem->getTitle());
			
			expectedString = "event two";
			testString = "event two 3 oct to 5 oct";
			myParser.detectTitleAndEmbed(myItem, testString);
			Assert::AreEqual(expectedString, myItem->getTitle());

			//expectedString = "assignment 5";
			//testString = "assignment 5 3 oct to 5 oct";
			//myParser.detectTitleAndEmbed(myItem, testString);
			//Assert::AreEqual(expectedString, myItem->getTitle());
		}

			TEST_METHOD(TestEmbedDate)
		{
			const int buffer_size = 256;
			char buffer[256];
			Parser myParser;
			Item* myItem = new Item;
			bool isDeadline = false;
			string testString = "dinner reserve at 8pm on 3 Sep";
			

			myParser.detectMonthDateAndEmbedIsOk(myItem, testString, isDeadline);
			strftime (buffer, buffer_size ,"%d %b",&myItem->getStartDateTime());
			Assert::AreEqual("03 Sep", buffer);

			testString = "dinner reserve on 17 Sep at 8pm";
			myParser.detectMonthDateAndEmbedIsOk(myItem, testString, isDeadline);
			strftime (buffer, buffer_size ,"%d %b",&myItem->getStartDateTime());
			Assert::AreEqual("17 Sep", buffer);

			testString = "dinner reserve on Sep 23 at 8pm";
			myParser.detectMonthDateAndEmbedIsOk(myItem, testString, isDeadline);
			strftime (buffer, buffer_size ,"%d %b",&myItem->getStartDateTime());
			Assert::AreEqual("23 Sep", buffer);

			testString = "dinner reserve on August 30";
			myParser.detectMonthDateAndEmbedIsOk(myItem, testString, isDeadline);
			strftime (buffer, buffer_size ,"%d %b",&myItem->getStartDateTime());
			Assert::AreEqual("30 Aug", buffer);


		}


		TEST_METHOD(TestEmbedTime)
		{
			const int buffer_size = 256;
			char buffer[256];


			Parser myParser;
			Item* myItem = new Item;
			bool isDeadline = false;
			myParser.detectTimeAndEmbedIsOk(myItem, "dinner reserve from 7.30pm to 9pm", isDeadline);
	

			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("07:30PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("09:00PM.", buffer);
			
			myParser.detectTimeAndEmbedIsOk(myItem, "dinner reserve 2:20pm to 3pm", isDeadline);
			
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("02:20PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("03:00PM.", buffer);

			myParser.detectTimeAndEmbedIsOk(myItem, "dinner reserve from 1pm - 3pm", isDeadline);
			
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("01:00PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("03:00PM.", buffer);

			myParser.detectTimeAndEmbedIsOk(myItem, "dinner between 1pm and 3pm", isDeadline);
			
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("01:00PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("03:00PM.", buffer);

			myParser.detectTimeAndEmbedIsOk(myItem, "dinner reserve at 2pm", isDeadline);
			
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("02:00PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("03:00PM.", buffer);
			
		}
			TEST_METHOD(TestSetDefaultStartTime)
		{
			const int buffer_size = 256;
			char buffer1[256];
			char buffer2[256];
			time_t rawtime=0;
			struct tm  timeinfo;
			localtime_s (&timeinfo, &rawtime); 

			Item* myItem = new Item;

			
			strftime (buffer1, buffer_size,"Now it's %c.",&timeinfo);
			strftime (buffer2, buffer_size ,"Now it's %c.",&myItem->getStartDateTime());
			Assert::AreEqual(buffer1, buffer2);
			
		}

			TEST_METHOD(TestEmbedTitleAndDateTime)
		{
			const int buffer_size = 256;
			char buffer[256];

			Parser myParser;
			Item* myItem = new Item;
			string expectedString="busy period";
			myParser.embedDetailsInItem(myItem, "busy period on 20 Sep from 1.30am to 9pm");
			Assert::AreEqual(expectedString, myItem->getTitle());
			strftime (buffer, buffer_size ,"%d %b %I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("20 Sep 01:30AM.", buffer);
			strftime (buffer, buffer_size ,"%d %b %I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("20 Sep 09:00PM.", buffer);
			
		}
			TEST_METHOD(TestExecutor1)
		{
			Executor* myExec = new Executor();
			//ItemBank* myIB = new ItemBank();
			//DisplayScreenConstructor* myDSC = DisplayScreenConstructor::getInstance();
			//OutputControl* myOC = new OutputControl();

			myExec->execute("add wake up on 30 Dec at 7 #category (more info)");

		
			Assert::AreEqual("wake up", OutputControl::getItemAddr(1)->getTitle().c_str());
			Assert::AreEqual("Tuesday 30 Dec 07:00AM", OutputControl::getItemAddr(1)->getStartDateInString().c_str());
			Assert::AreEqual("Tuesday 30 Dec 08:00AM", OutputControl::getItemAddr(1)->getEndDateInString().c_str());
			Assert::AreEqual("category", OutputControl::getItemAddr(1)->getCategory().c_str());
			Assert::AreEqual("more info", OutputControl::getItemAddr(1)->getDescription().c_str());
			Assert::AreEqual("Low", OutputControl::getItemAddr(1)->getPriorityInString().c_str());
		
			try{
				myExec->execute("add more info(");
			}
			catch (exception& e){
				Assert::AreEqual("Invalid brackets! Please follow e.g. add event at 7pm (description)", e.what() );
			}
		}
	};
}