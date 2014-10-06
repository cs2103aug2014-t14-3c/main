#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLeon
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestStringToHourInt)
		{
			Parser myParser;
			Assert::AreEqual(myParser.convertStringToIntHour("5pm"), 17);
			Assert::AreEqual(myParser.convertStringToIntHour("9PM"), 21);
			Assert::AreEqual(myParser.convertStringToIntHour("12"), 12);
			Assert::AreEqual(myParser.convertStringToIntHour("11am"), 11);
			Assert::AreEqual(myParser.convertStringToIntHour("1AM"), 1);
		}

		TEST_METHOD(TestStringToMinInt)
		{
			Parser myParser;
			Assert::AreEqual(30, myParser.convertStringToIntMin("5.30pm"));
			Assert::AreEqual(50, myParser.convertStringToIntMin("7:50am"));
			Assert::AreEqual(59, myParser.convertStringToIntMin("2.59"));
			Assert::AreEqual(0, myParser.convertStringToIntMin("5:00"));
		}

		TEST_METHOD(TestEmbedTitle)
		{
			Parser myParser;
			Item* myItem = new Item;
			string expectedString = "dinner reserve";
			myParser.detectTitleAndEmbed(myItem, "dinner reserve at 8pm on 3 Sep");
			Assert::AreEqual(expectedString, myItem->getTitle());
			myParser.detectTitleAndEmbed(myItem, "dinner reserve on 3 Sep at 8pm ");
			Assert::AreEqual(expectedString, myItem->getTitle());
		}

			TEST_METHOD(TestEmbedDate)
		{
			const int buffer_size = 256;
			char buffer[256];
			Parser myParser;
			Item* myItem = new Item;

			myParser.detectDateAndEmbed(myItem, "dinner reserve at 8pm on 3 Sep");
			strftime (buffer, buffer_size ,"%d %b",&myItem->getStartDateTime());
			Assert::AreEqual("03 Sep", buffer);

			myParser.detectDateAndEmbed(myItem, "dinner reserve on 17 Sep at 8pm");
			strftime (buffer, buffer_size ,"%d %b",&myItem->getStartDateTime());
			Assert::AreEqual("17 Sep", buffer);
		}


		TEST_METHOD(TestEmbedTime)
		{
			const int buffer_size = 256;
			char buffer[256];


			Parser myParser;
			Item* myItem = new Item;
			myParser.detectTimeAndEmbed(myItem, "dinner reserve from 7.30pm to 9pm");
	

			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("07:30PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("09:00PM.", buffer);
			
			myParser.detectTimeAndEmbed(myItem, "dinner reserve 2:20pm to 3pm");
			
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("02:20PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("03:00PM.", buffer);

			myParser.detectTimeAndEmbed(myItem, "dinner reserve from 1pm - 3pm");
			
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("01:00PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("03:00PM.", buffer);

			myParser.detectTimeAndEmbed(myItem, "dinner reserve between 1pm and 3pm");
			
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getStartDateTime());
			Assert::AreEqual("01:00PM.", buffer);
			strftime (buffer, buffer_size ,"%I:%M%p.",&myItem->getEndDateTime());
			Assert::AreEqual("03:00PM.", buffer);
			
		}
			TEST_METHOD(TestSetDefaultStartTime)
		{
			const int buffer_size = 256;
			char buffer1[256];
			char buffer2[256];
			time_t rawtime;
			struct tm  timeinfo;
			time (&rawtime);
			localtime_s (&timeinfo, &rawtime); 

			Item* myItem = new Item;

			
			strftime (buffer1, buffer_size,"Now it's %I:%M%p.",&timeinfo);
			strftime (buffer2, buffer_size ,"Now it's %I:%M%p.",&myItem->getStartDateTime());
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
	};
}