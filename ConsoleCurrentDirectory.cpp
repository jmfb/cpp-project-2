#include <Wex/WindowsInclude.h>
#include "ConsoleCurrentDirectory.h"

ConsoleCurrentDirectory::ConsoleCurrentDirectory()
	: ConsoleCommand{ "pwd", {}, "Display the current directory." }
{
}

void ConsoleCurrentDirectory::Execute(
	Console& console,
	const std::vector<std::string>& arguments)
{
	ValidateArguments(arguments);
	console.WriteLine(console.GetCurrentDirectory());
}

