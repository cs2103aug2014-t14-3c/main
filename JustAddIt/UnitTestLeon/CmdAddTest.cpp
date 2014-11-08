#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string FILL = "This is a random filler text to test code";
const string DATE = "Saturday 15 Nov 2014 08:00AM";

namespace UnitTest
{		
	TEST_CLASS(CmdAdd)
	{
	public:
		
		TEST_METHOD(CmdAddTest) // all positive test case *using multiple input
		{
			/*
			Item* itemPtr = new Item;
			itemPtr->setTitle(FILL);
			itemPtr->setDescription(FILL);
			itemPtr->setVenue(FILL);
			itemPtr->setCategory(FILL);
			itemPtr->setStartDate(15, 10);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(15, 10);
			itemPtr->setEndTime(8, 0);

			Assert::AreEqual(itemPtr->getTitle(), FILL);
			Assert::AreEqual(itemPtr->getDescription(), FILL);
			Assert::AreEqual(itemPtr->getVenue(), FILL);
			Assert::AreEqual(itemPtr->getCategory(), FILL);
			Assert::AreEqual(itemPtr->getStartDateInString(), DATE);
			Assert::AreEqual(itemPtr->getEndDateInString(), DATE);
			*/
		}
	};
}