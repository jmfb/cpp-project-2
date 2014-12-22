#include <Wex/WindowsInclude.h>
#include "ConsoleNewProject.h"
#include <Wex/Path.h>
#include <Wex/File.h>
#include <stdexcept>

ConsoleNewProject::ConsoleNewProject()
	: ConsoleCommand{ "new", { "project-name" }, "Create a new project." }
{
}

void ConsoleNewProject::Execute(
	Console& console,
	const std::vector<std::string>& arguments)
{
	ValidateArguments(arguments);
	const auto& name = arguments[0];
	auto projectDirectory = Wex::Path::Combine(
		console.GetCurrentDirectory(),
		name);
	auto fullPath = Wex::Path::Combine(
		projectDirectory,
		name + ".cpp-project");
	if (Wex::File::Exists(fullPath))
		throw std::runtime_error{ "Project already exists." };
	console.NewProject(name);
}

