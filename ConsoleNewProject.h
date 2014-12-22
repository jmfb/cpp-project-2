#pragma once
#include "ConsoleCommand.h"
#include "Console.h"

class ConsoleNewProject : public ConsoleCommand
{
public:
	ConsoleNewProject();
	ConsoleNewProject(const ConsoleNewProject& rhs) = default;
	~ConsoleNewProject() = default;

	ConsoleNewProject& operator=(const ConsoleNewProject& rhs) = default;

	void Execute(Console& console, const std::vector<std::string>& arguments);

private:
	friend class ConsoleNewProjectTest;
};

