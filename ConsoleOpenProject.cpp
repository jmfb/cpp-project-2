#include <Wex/WindowsInclude.h>
#include "ConsoleOpenProject.h"
#include <stdexcept>

ConsoleOpenProject::ConsoleOpenProject()
	: ConsoleCommand{ "open", { "project-name" }, "Opens the given project." }
{
}

void ConsoleOpenProject::Execute(const std::vector<std::string>& arguments)
{
	ValidateArguments(arguments);
	OpenProject(arguments[0]);
}

void ConsoleOpenProject::OpenProject(const std::string& projectName)
{
	//TODO: open that guy
}

