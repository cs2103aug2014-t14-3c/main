#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const string MESSAGE_EXPORT_SUCCESSFUL = "The current screen has been exported into text file \"JustAddIt_Exports.txt\"!";

namespace UnitTest
{		
	TEST_CLASS(CmdExportTest)
	{
	public:

		TEST_METHOD(CmdExport_SuccessMessageTest)
		{
			CmdExport* cmdExport = new CmdExport();
			vector<string> outputMessageStorage = cmdExport->execute();
			Assert::AreEqual(outputMessageStorage.back(), MESSAGE_EXPORT_SUCCESSFUL);
		}

		TEST_METHOD(CmdExport_FinalStorageSizeTest)
		{
			CmdExport* cmdExport = new CmdExport();
			vector<string> outputMessageStorage = cmdExport->execute();
			Assert::AreEqual((int)outputMessageStorage.size(), 1);
		}
	};
}