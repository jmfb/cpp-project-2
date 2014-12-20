#include <Wex/WindowsInclude.h>
#include "ConsoleExit.h"
#include <stdexcept>

ConsoleExit::ConsoleExit()
	: ConsoleCommand{ "exit", {}, "Exits the application." }
{
}

void ConsoleExit::Execute(const std::vector<std::string>& arguments)
{
	ValidateArguments(arguments);
	Exit();
}

void ConsoleExit::Exit()
{
	//TODO: Perform application shutdown?
	::PostQuitMessage(0);
}

