#pragma once
#include "ConsoleCommand.h"
#include "Console.h"

class ConsoleOpenProject : public ConsoleCommand
{
public:
	ConsoleOpenProject();
	ConsoleOpenProject(const ConsoleOpenProject& rhs) = default;
	~ConsoleOpenProject() = default;

	ConsoleOpenProject& operator=(const ConsoleOpenProject& rhs) = default;

	void Execute(Console& console, const std::vector<std::string>& arguments);
	void OpenProject(Console& console, const std::string& projectName);

private:
	friend class ConsoleOpenProjectTest;
};

