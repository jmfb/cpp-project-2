#include <Wex/WindowsInclude.h>
#include "ConsoleOpenProject.h"
#include <Wex/Path.h>
#include <Wex/File.h>
#include <Wex/Exception.h>

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
	//TODO: allow user to change this
	const std::string currentDirectory = R"(c:\save\code)";

	auto fullPath = Wex::Path::Combine(currentDirectory, projectName + ".cpp-project");
	if (!Wex::File::Exists(fullPath))
		fullPath = Wex::Path::Combine(currentDirectory,
			projectName + "\\" + projectName + ".cpp-project");
	CheckError(!Wex::File::Exists(fullPath), 0, "File does not exist.");

	//TODO: something
}

