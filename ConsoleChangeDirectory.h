#pragma once
#include "ConsoleCommand.h"
#include "Console.h"

class ConsoleChangeDirectory : public ConsoleCommand
{
public:
	ConsoleChangeDirectory();
	ConsoleChangeDirectory(const ConsoleChangeDirectory& rhs) = default;
	~ConsoleChangeDirectory() = default;

	ConsoleChangeDirectory& operator=(const ConsoleChangeDirectory& rhs) = default;

	void Execute(Console& console, const std::vector<std::string>& arguments);

private:
	friend class ConsoleChangeDirectoryTest;
};

