#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string FILL = "This is a random filler text to test code";
const string DATE = "Thursday 23 Oct 08:00AM";

namespace UnitTestLeon
{		
	TEST_CLASS(AddTest)
	{
	public:
		
		TEST_METHOD(CmdAdd) // all positive test case *using multiple input
		{
			Item* itemPtr;
			itemPtr = new Item;
			itemPtr->setTitle(FILL);
			itemPtr->setDescription(FILL);
			itemPtr->setVenue(FILL);
			itemPtr->setCategory(FILL);
			itemPtr->setStartDate(23, 9);
			itemPtr->setStartTime(8, 0);
			itemPtr->setEndDate(23, 9);
			itemPtr->setEndTime(8, 0);

			
			Assert::AreEqual(itemPtr->getTitle(), FILL);
			Assert::AreEqual(itemPtr->getDescription(), FILL);
			Assert::AreEqual(itemPtr->getVenue(), FILL);
			Assert::AreEqual(itemPtr->getCategory(), FILL);
			Assert::AreEqual(itemPtr->getStartDateInString(), DATE);
			Assert::AreEqual(itemPtr->getEndDateInString(), DATE);
		}
	};
}