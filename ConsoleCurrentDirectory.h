#pragma once
#include "ConsoleCommand.h"
#include "Console.h"

class ConsoleCurrentDirectory : public ConsoleCommand
{
public:
	ConsoleCurrentDirectory();
	ConsoleCurrentDirectory(const ConsoleCurrentDirectory& rhs) = default;
	~ConsoleCurrentDirectory() = default;

	ConsoleCurrentDirectory& operator=(const ConsoleCurrentDirectory& rhs) = default;

	void Execute(Console& console, const std::vector<std::string>& arguments);

private:
	friend class ConsoleCurrentDirectoryTest;
};

