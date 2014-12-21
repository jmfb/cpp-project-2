#pragma once
#include "ConsoleCommand.h"
#include "Console.h"

class ConsoleExit : public ConsoleCommand
{
public:
	ConsoleExit();
	ConsoleExit(const ConsoleExit& rhs) = default;
	~ConsoleExit() = default;

	ConsoleExit& operator=(const ConsoleExit& rhs) = default;

	void Execute(Console& console, const std::vector<std::string>& arguments);

private:
	friend class ConsoleExitTest;
};

