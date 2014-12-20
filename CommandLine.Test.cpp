#include "CommandLine.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

TEST_CLASS(CommandLineTest)
{
public:
	CommandLineTest()
	{
	}

	TEST_METHOD(Flags)
	{
		const char* argv[] = { "/a", "-b", "c", "/d=1" };
		CommandLine arguments{ 4, argv };
		Assert.IsTrue(arguments.GetFlag("a"));
		Assert.IsTrue(arguments.GetFlag("b"));
		Assert.IsFalse(arguments.GetFlag("c"));
		Assert.IsFalse(arguments.GetFlag("d"));
		Assert.IsFalse(arguments.GetFlag("e"));
	}

	TEST_METHOD(Settings)
	{
		const char* argv[] = { "/a=1", "-b=2", "/c", "d" };
		CommandLine arguments{ 4, argv };
		Assert.AreEqual(std::string{ "1" }, arguments.GetSetting("a"));
		Assert.AreEqual(std::string{ "2" }, arguments.GetSetting("b"));
		Assert.AreEqual(std::string{}, arguments.GetSetting("c"));
		Assert.AreEqual(std::string{}, arguments.GetSetting("d"));
		Assert.AreEqual(std::string{}, arguments.GetSetting("e"));
	}

	TEST_METHOD(DuplicateSetting)
	{
		const char* argv[] = { "/a=1", "/a=2" };
		CommandLine arguments{ 2, argv };
		Assert.AreEqual(std::string{ "2" }, arguments.GetSetting("a"));
	}

	TEST_METHOD(Targets)
	{
		const char* argv[] = { "a", "/b", "/c=1", "d" };
		CommandLine arguments{ 4, argv };
		auto targets = arguments.GetTargets();
		Assert.AreEqual(2ull, targets.size());
		Assert.AreEqual(std::string{ "a" }, targets[0]);
		Assert.AreEqual(std::string{ "d" }, targets[1]);
	}
};

