#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string FILL = "This is a random filler text to test code";
const string DATE = "Thursday 20 Nov 2014 08:00AM";

namespace UnitTest
{		
	TEST_CLASS(ItemTest)
	{
	public:
		
		TEST_METHOD(Item_Pos) // all positive test case *using multiple input
		{
			Item* itemPtr = new Item;
			itemPtr->setTitle(FILL);
			itemPtr->setDescription(FILL);
			itemPtr->setVenue(FILL);
			itemPtr->setCategory(FILL);
			itemPtr->setStartDate(20, 10);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(20, 10);
			itemPtr->setEndTime(8, 0);

			Assert::AreEqual(FILL, itemPtr->getTitle());
			Assert::AreEqual(FILL, itemPtr->getDescription());
			Assert::AreEqual(FILL, itemPtr->getVenue());
			Assert::AreEqual(FILL, itemPtr->getCategory());
			Assert::AreEqual(DATE, itemPtr->getStartDateInString());
			Assert::AreEqual(DATE, itemPtr->getEndDateInString());
		}
	};
}