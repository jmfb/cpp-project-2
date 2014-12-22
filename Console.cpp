#include <Wex/WindowsInclude.h>
#include "Console.h"
#include "ColorScheme.h"
#include "ConsoleCommandParser.h"
#include "ConsoleChangeDirectory.h"
#include "ConsoleDirectoryList.h"
#include "ConsoleNewProject.h"
#include "ConsoleOpenProject.h"
#include "ConsoleCloseProject.h"
#include "ConsoleExit.h"
#include <tuple>
#include <sstream>
#include <iostream>

bool Console::ConsoleMode::Execute(
	std::tuple<>,
	Console& console,
	const ConsoleCommandParser& parsedCommand)
{
	return false;
}

std::vector<ConsoleCommand> Console::ConsoleMode::GetCommands(
	std::tuple<>)
{
	return {};
}

const Console::ConsoleMode Console::Initial =
	Console::ConsoleMode::Create<std::tuple<
		ConsoleNewProject,
		ConsoleOpenProject,
		ConsoleChangeDirectory,
		ConsoleDirectoryList,
		ConsoleExit
	>>([](const Console& console){ return console.GetCurrentDirectory() + "> "; });

const Console::ConsoleMode Console::Project =
	Console::ConsoleMode::Create<std::tuple<
		ConsoleCloseProject,
		ConsoleExit
	>>([](const Console& console){ return console.GetCurrentProjectName() + "> "; });

Console::Console(ConsoleEvents& events)
	: events{ &events }, mode{ &Initial }
{
}

void Console::SwitchMode(const ConsoleMode& value)
{
	mode = &value;
}

void Console::ExecuteCommand(const std::string& command)
{
	ConsoleCommandParser parsedCommand{ command };
	errorCommand.clear();
	errorMessage.clear();
	messages.clear();
	try
	{
		if (!mode->executeCommand(*this, parsedCommand))
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

std::string Console::GetPrompt() const
{
	return mode->getPrompt(*this);
}

ColoredLines Console::GetDisplay() const
{
	auto commands = mode->getCommands();
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
			prompt.push_back(message);
	}

	return prompt;
}

void Console::WriteLine(const std::string& message)
{
	messages.push_back({ { ColorScheme::Console::Default, message } });
}

void Console::WriteLine(const ColoredLine& message)
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

const std::string& Console::GetCurrentProjectName() const
{
	return currentProjectName;
}

void Console::SetCurrentProjectName(const std::string& value)
{
	currentProjectName = value;
}

void Console::NewProject(const std::string& name)
{
	events->OnNewProject(name);
}

void Console::OpenProject(const std::string& fullPath)
{
	events->OnOpenProject(fullPath);
}

void Console::CloseProject()
{
	events->OnCloseProject();
}

void Console::Exit()
{
	events->OnExit();
}

