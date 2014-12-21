#include <Wex/WindowsInclude.h>
#include "ConsoleExit.h"
#include <stdexcept>

ConsoleExit::ConsoleExit()
	: ConsoleCommand{ "exit", {}, "Exits the application." }
{
}

void ConsoleExit::Execute(Console& console, const std::vector<std::string>& arguments)
{
	ValidateArguments(arguments);
	console.Exit();
}

