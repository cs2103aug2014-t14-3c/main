//@author A0110770U
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(ParserTest)
	{
	public:
		
		TEST_METHOD(Parser_StringToHourInt)
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

		TEST_METHOD(Parser_StringToMinInt)
		{
			Parser myParser;
			Assert::AreEqual(30, myParser.convertStringToIntMin("5.30pm"));
			Assert::AreEqual(50, myParser.convertStringToIntMin("7:50am"));
			Assert::AreEqual(59, myParser.convertStringToIntMin("2.59"));
			Assert::AreEqual(0, myParser.convertStringToIntMin("5:00"));
			Assert::AreEqual(0, myParser.convertStringToIntMin("5:00"));
		}

		TEST_METHOD(Parser_EmbedTitle)
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

			TEST_METHOD(Parser_EmbedDate)
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


		TEST_METHOD(Parser_EmbedTime)
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
			TEST_METHOD(Parser_SetDefaultStartTime)
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

			TEST_METHOD(Parser_EmbedTitleAndDateTime)
		{
			const int buffer_size = 256;
			char buffer[256];
			

			Parser myParser;
			Item* myItem = new Item;

			myParser.embedDetailsInItem(myItem, "busy period on 20 Sep from 1.30am to 9pm");
			Assert::AreEqual("busy period", myItem->getTitle().c_str());
			strftime (buffer, buffer_size ,"%d %b %I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("20 Sep 01:30AM.", buffer);
			strftime (buffer, buffer_size ,"%d %b %I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("20 Sep 09:00PM.", buffer);
			
		}
			TEST_METHOD(Parser_NegativeTestExceptions)
		{
			const int buffer_size = 256;
			char buffer[256];
			

			Parser myParser;
			Item* myItem = new Item;

			try{
				myParser.embedDetailsInItem(myItem, "20 Sep from 1.30am to 9pm");
			}
			catch (exception& e){
				Assert::AreEqual(Parser::ERROR_MISSING_TITLE.c_str(), e.what() );
			}
			try{
				myParser.embedDetailsInItem(myItem, "assignment 2 (physics");
			}
			catch (exception& e){
				Assert::AreEqual(Parser::ERROR_INVALID_BRACKETS.c_str(), e.what() );
			}
			try{
				myParser.embedDetailsInItem(myItem, "assignment 2 physics)");
			}
			catch (exception& e){
				Assert::AreEqual(Parser::ERROR_INVALID_BRACKETS.c_str(), e.what() );
			}
			
			
		}
			TEST_METHOD(Parser_UserGuideExamples)
		{
			const int buffer_size = 256;
			char expectedBuffer[256];
			char actualBuffer[256];
			Parser myParser;
			Item* myItem = new Item;

			time_t nowTime;
			tm nowTimeTM;
			time(&nowTime);
			localtime_s (&nowTimeTM, &nowTime);


			myParser.embedDetailsInItem(myItem, "band practice at 5pm next Tuesday !!");

			Assert::AreEqual("band practice", myItem->getTitle().c_str());
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("18 Nov 2014 05:00PM.", actualBuffer);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("18 Nov 2014 06:00PM.", actualBuffer);
			Assert::AreEqual("High", myItem->getPriorityInString().c_str());

			myParser.embedDetailsInItem(myItem, "Dinner date (buy flowers) on 14 February at 9PM");

			Assert::AreEqual("Dinner date", myItem->getTitle().c_str());
			Assert::AreEqual("buy flowers", myItem->getDescription().c_str());
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("14 Feb 2015 09:00PM.", actualBuffer);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("14 Feb 2015 10:00PM.", actualBuffer);

			myParser.embedDetailsInItem(myItem, "project meeting from 5:30pm - 9pm #school");

			Assert::AreEqual("project meeting", myItem->getTitle().c_str());
			Assert::AreEqual("school", myItem->getCategory().c_str());
			strftime (expectedBuffer, buffer_size ,"%d %b %Y", &nowTimeTM);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getStartDateTime());
			strcat_s(expectedBuffer, buffer_size, " 05:30PM.");
			Assert::AreEqual(expectedBuffer, actualBuffer);

			strftime (expectedBuffer, buffer_size ,"%d %b %Y", &nowTimeTM);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			strcat_s(expectedBuffer, buffer_size, " 09:00PM.");
			Assert::AreEqual(expectedBuffer, actualBuffer);

			myParser.embedDetailsInItem(myItem, "Holiday period from 10 May - 10 Jul");

			Assert::AreEqual("Holiday period", myItem->getTitle().c_str());
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("10 May 2015 12:00AM.", actualBuffer);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("10 Jul 2015 11:59PM.", actualBuffer);

			myParser.embedDetailsInItem(myItem, "Presentation slot 1.40pm - 1400");

			Assert::AreEqual("Presentation slot", myItem->getTitle().c_str());
			
			strftime (expectedBuffer, buffer_size ,"%d %b %Y", &nowTimeTM);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getStartDateTime());
			strcat_s(expectedBuffer, buffer_size, " 01:40PM.");
			Assert::AreEqual(expectedBuffer, actualBuffer);

			strftime (expectedBuffer, buffer_size ,"%d %b %Y", &nowTimeTM);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			strcat_s(expectedBuffer, buffer_size, " 02:00PM.");
			Assert::AreEqual(expectedBuffer, actualBuffer);

			myParser.embedDetailsInItem(myItem, "night cycling event today 2.20 - 4am");
			
			Assert::AreEqual("night cycling event", myItem->getTitle().c_str());
			
			strftime (expectedBuffer, buffer_size ,"%d %b %Y", &nowTimeTM);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getStartDateTime());
			strcat_s(expectedBuffer, buffer_size, " 02:20AM.");
			Assert::AreEqual(expectedBuffer, actualBuffer);

			strftime (expectedBuffer, buffer_size ,"%d %b %Y", &nowTimeTM);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			strcat_s(expectedBuffer, buffer_size, " 04:00AM.");
			Assert::AreEqual(expectedBuffer, actualBuffer);

			myParser.embedDetailsInItem(myItem, "submit assignment due 8pm !");
			
			Assert::AreEqual("submit assignment", myItem->getTitle().c_str());
			
			strftime (expectedBuffer, buffer_size ,"%d %b %Y", &nowTimeTM);
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			strcat_s(expectedBuffer, buffer_size, " 08:00PM.");
			Assert::AreEqual(expectedBuffer, actualBuffer);
			Assert::AreEqual("deadline", myItem->getItemTypeInString().c_str());
			Assert::AreEqual("Medium", myItem->getPriorityInString().c_str());

			myParser.embedDetailsInItem(myItem, "Book flight by tomorrow (change currency)");
			
			Assert::AreEqual("Book flight", myItem->getTitle().c_str());
			nowTimeTM.tm_mday++;
			mktime(&nowTimeTM);
			strftime (expectedBuffer, buffer_size ,"%d %b %Y", &nowTimeTM);
			
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			strcat_s(expectedBuffer, buffer_size, " 11:59PM.");
			Assert::AreEqual(expectedBuffer, actualBuffer);
			Assert::AreEqual("deadline", myItem->getItemTypeInString().c_str());
			Assert::AreEqual("change currency", myItem->getDescription().c_str());
			time(&nowTime);
			localtime_s (&nowTimeTM, &nowTime);

			myParser.embedDetailsInItem(myItem, "complete job by 28 March 9pm");
		
			Assert::AreEqual("complete job", myItem->getTitle().c_str());
			
			strftime (actualBuffer, buffer_size ,"%d %b %Y %I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("28 Mar 2015 09:00PM.", actualBuffer);

			Assert::AreEqual("deadline", myItem->getItemTypeInString().c_str());

			myParser.embedDetailsInItem(myItem, "call Sarah");
		
			Assert::AreEqual("call Sarah", myItem->getTitle().c_str());
			Assert::AreEqual("task", myItem->getItemTypeInString().c_str());

			myParser.embedDetailsInItem(myItem, "Clean dormitory room #personal");
		
			Assert::AreEqual("Clean dormitory room", myItem->getTitle().c_str());
			Assert::AreEqual("task", myItem->getItemTypeInString().c_str());
			Assert::AreEqual("personal", myItem->getCategory().c_str());
}
	};
}