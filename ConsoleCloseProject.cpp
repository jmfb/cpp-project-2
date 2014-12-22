#include <Wex/WindowsInclude.h>
#include "ConsoleCloseProject.h"

ConsoleCloseProject::ConsoleCloseProject()
	: ConsoleCommand{ "close", {}, "Close the project." }
{
}

void ConsoleCloseProject::Execute(
	Console& console,
	const std::vector<std::string>& arguments)
{
	ValidateArguments(arguments);
	console.CloseProject();
}

