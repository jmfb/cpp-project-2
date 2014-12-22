#pragma once
#include "ConsoleCommand.h"
#include "Console.h"

class ConsoleCloseProject : public ConsoleCommand
{
public:
	ConsoleCloseProject();
	ConsoleCloseProject(const ConsoleCloseProject& rhs) = default;
	~ConsoleCloseProject() = default;

	ConsoleCloseProject& operator=(const ConsoleCloseProject& rhs) = default;

	void Execute(
		Console& console,
		const std::vector<std::string>& arguments);

private:
	friend class ConsoleCloseProjectTest;
};

