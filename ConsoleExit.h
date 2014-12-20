#pragma once
#include "ConsoleCommand.h"

class ConsoleExit : public ConsoleCommand
{
public:
	ConsoleExit();
	ConsoleExit(const ConsoleExit& rhs) = default;
	~ConsoleExit() = default;

	ConsoleExit& operator=(const ConsoleExit& rhs) = default;

	void Execute(const std::vector<std::string>& arguments);
	void Exit();

private:
	friend class ConsoleExitTest;
};

