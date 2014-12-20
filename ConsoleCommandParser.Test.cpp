#include "ConsoleCommandParser.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

TEST_CLASS(ConsoleCommandParserTest)
{
public:
	ConsoleCommandParserTest()
	{
	}

	TEST_METHOD(StandardUsage)
	{
		ConsoleCommandParser command{ R"( open "cpp project" true )" };
		Assert.AreEqual(std::string{ "open" }, command.GetName());
		const auto& arguments = command.GetArguments();
		Assert.AreEqual(2, arguments.size());
		Assert.AreEqual(std::string{ "cpp project" }, arguments[0]);
		Assert.AreEqual(std::string{ "true" }, arguments[1]);
	}

	TEST_METHOD(UnmatchedQuotes)
	{
		ConsoleCommandParser command{ R"(open "cpp project)" };
		Assert.AreEqual(std::string{ "open" }, command.GetName());
		const auto& arguments = command.GetArguments();
		Assert.AreEqual(1, arguments.size());
		Assert.AreEqual(std::string{ "cpp project" }, arguments[0]);
	}
};

