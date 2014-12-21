#include <Wex/WindowsInclude.h>
#include "ConsoleChangeDirectory.h"
#include <Wex/Path.h>
#include <Wex/Directory.h>
#include <stdexcept>

ConsoleChangeDirectory::ConsoleChangeDirectory()
	: ConsoleCommand{ "cd", { "directory-name" }, "Change the current directory." }
{
}

void ConsoleChangeDirectory::Execute(Console& console, const std::vector<std::string>& arguments)
{
	ValidateArguments(arguments);
	auto currentDirectory = console.GetCurrentDirectory();
	auto directory = Wex::Path::Combine(currentDirectory, arguments[0]);
	directory = Wex::Path::GetAbsolutePath(directory);
	if (!Wex::Directory::Exists(directory))
		throw std::runtime_error{ "Directory does not exist." };
	console.SetCurrentDirectory(directory);
}

