#pragma once
#include "ConsoleCommand.h"

class ConsoleOpenProject : public ConsoleCommand
{
public:
	ConsoleOpenProject();
	ConsoleOpenProject(const ConsoleOpenProject& rhs) = default;
	~ConsoleOpenProject() = default;

	ConsoleOpenProject& operator=(const ConsoleOpenProject& rhs) = default;

	void Execute(const std::vector<std::string>& arguments);
	void OpenProject(const std::string& projectName);

private:
	friend class ConsoleOpenProjectTest;
};

