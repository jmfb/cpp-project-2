#include <Wex/WindowsInclude.h>
#include "Console.h"
#include "ColorScheme.h"
#include "ConsoleCommandParser.h"
#include "ConsoleOpenProject.h"
#include "ConsoleExit.h"
#include <tuple>

using Commands = std::tuple<
	ConsoleOpenProject,
	ConsoleExit
>;

bool Execute(std::tuple<>, const ConsoleCommandParser& parsedCommand)
{
	return false;
}

template <typename Command, typename... Commands>
bool Execute(std::tuple<Command, Commands...>, const ConsoleCommandParser& parsedCommand)
{
	Command command;
	if (command.GetName() != parsedCommand.GetName())
		return Execute(std::tuple<Commands...>{}, parsedCommand);
	command.Execute(parsedCommand.GetArguments());
	return true;
}

void Console::ExecuteCommand(const std::string& command)
{
	ConsoleCommandParser parsedCommand{ command };
	errorCommand.clear();
	errorMessage.clear();
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

std::vector<ConsoleCommand> GetCommands(std::tuple<>)
{
	return {};
}

template <typename Command, typename... Commands>
std::vector<ConsoleCommand> GetCommands(std::tuple<Command, Commands...>)
{
	std::vector<ConsoleCommand> commands;
	commands.push_back(Command{});
	for (const auto& command : GetCommands(std::tuple<Commands...>{}))
		commands.push_back(command);
	return commands;
}

ColoredLines Console::GetPrompt(const std::string& partialCommand) const
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
		prompt.push_back({ { ColorScheme::Console::Error, errorMessage } });
	}
	return prompt;
}

