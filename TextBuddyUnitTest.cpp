#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyUnitTest
{		
	TEST_CLASS(TrimTest)
	{
	public:

		TEST_METHOD(TrimRightTest)
		{
			TextBuddy* myTextBuddy = new TextBuddy ("test.txt");
			std::string inputLine = "Hello         ";
			inputLine = myTextBuddy->trimWhiteSpace(inputLine, " ");
			std::string expectedLine = "Hello";
			Assert::AreEqual(inputLine, expectedLine);
		}

		TEST_METHOD(TrimLeftTest)
		{
			TextBuddy* myTextBuddy = new TextBuddy ("test.txt");
			std::string inputLine = "         Hello";
			inputLine = myTextBuddy->trimWhiteSpace(inputLine, " ");
			std::string expectedLine = "Hello";
			Assert::AreEqual(inputLine, expectedLine);
		}

		TEST_METHOD(TrimAllTest)
		{
			TextBuddy* myTextBuddy = new TextBuddy ("test.txt");
			std::string inputLine = "         Hello        ";
			inputLine = myTextBuddy->trimWhiteSpace(inputLine, " ");
			std::string expectedLine = "Hello";
			Assert::AreEqual(inputLine, expectedLine);
		}
	};

	TEST_CLASS(AddLineTest)
	{
	public:

		TEST_METHOD(TrimTest_LineCounterTest)
		{
			TextBuddy* myTextBuddy = new TextBuddy ("test.txt");
			std::string inputLine = myTextBuddy->addLineFromUser ("     Hellooo     ");
			std::string expectedLine = "Hellooo";
			Assert::AreEqual(inputLine, expectedLine);
			int expectedLineCount = 1;
			int outputLineCount = myTextBuddy->getLineCounter();
			Assert::AreEqual(outputLineCount, expectedLineCount);
		}


	};
}