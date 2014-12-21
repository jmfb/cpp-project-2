#include <Wex/WindowsInclude.h>
#include "ConsoleOpenProject.h"
#include <Wex/Path.h>
#include <Wex/File.h>
#include <stdexcept>

ConsoleOpenProject::ConsoleOpenProject()
	: ConsoleCommand{ "open", { "project-name" }, "Opens the given project." }
{
}

void ConsoleOpenProject::Execute(Console& console, const std::vector<std::string>& arguments)
{
	ValidateArguments(arguments);
	OpenProject(console, arguments[0]);
}

void ConsoleOpenProject::OpenProject(Console& console, const std::string& projectName)
{
	auto currentDirectory = console.GetCurrentDirectory();
	auto fullPath = Wex::Path::Combine(currentDirectory, projectName + ".cpp-project");
	if (!Wex::File::Exists(fullPath))
		fullPath = Wex::Path::Combine(currentDirectory,
			projectName + "\\" + projectName + ".cpp-project");
	if (!Wex::File::Exists(fullPath))
		throw std::runtime_error{ "File does not exist." };
	console.OpenProject(fullPath);
}

