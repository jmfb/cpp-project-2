#include <Wex/WindowsInclude.h>
#include "Console.h"
#include "ColorScheme.h"
#include "ConsoleCommandParser.h"
#include "ConsoleChangeDirectory.h"
#include "ConsoleDirectoryList.h"
#include "ConsoleOpenProject.h"
#include "ConsoleExit.h"
#include <tuple>
#include <sstream>
#include <iostream>

using Commands = std::tuple<
	ConsoleOpenProject,
	ConsoleChangeDirectory,
	ConsoleDirectoryList,
	ConsoleExit
>;

void Console::ExecuteCommand(const std::string& command)
{
	ConsoleCommandParser parsedCommand{ command };
	errorCommand.clear();
	errorMessage.clear();
	messages.clear();
	try
	{
		if (!Execute(Commands{}, parsedCommand))
		{
			errorCommand = command;
			errorMessage = "Invalid command";
		}
	}
	catch (const std::exception& exception)
	{
		errorCommand = command;
		errorMessage = exception.what();
	}
}

ColoredLines Console::GetPrompt() const
{
	auto commands = GetCommands(Commands{});
	auto maxCommandLength = 0;
	for (const auto& command : commands)
		maxCommandLength = std::max(maxCommandLength, command.GetCommandLength());

	ColoredLines prompt;
	for (const auto& command : commands)
		prompt.push_back(command.GetPrompt(maxCommandLength + 1));

	if (!errorCommand.empty())
	{
		prompt.push_back({});
		prompt.push_back({ { ColorScheme::Console::Default, errorCommand } });
		std::string errorLine;
		std::istringstream errors{ errorMessage };
		while (std::getline(errors, errorLine))
			prompt.push_back({ { ColorScheme::Console::Error, errorLine } });
	}

	if (!messages.empty())
	{
		prompt.push_back({});
		for (const auto& message : messages)
			prompt.push_back({ { ColorScheme::Console::Default, message } });
	}

	return prompt;
}

void Console::WriteLine(const std::string& message)
{
	messages.push_back(message);
}

const std::string& Console::GetCurrentDirectory() const
{
	return currentDirectory;
}

void Console::SetCurrentDirectory(const std::string& value)
{
	currentDirectory = value;
}

void Console::OpenProject(const std::string& fullPath)
{
}

void Console::Exit()
{
	::PostQuitMessage(0);
}

bool Console::Execute(
	std::tuple<>,
	const ConsoleCommandParser& parsedCommand)
{
	return false;
}

std::vector<ConsoleCommand> Console::GetCommands(std::tuple<>) const
{
	return {};
}

