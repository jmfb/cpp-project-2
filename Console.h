#pragma once
#include <vector>
#include <string>
#include "ColoredText.h"
#include "ConsoleCommandParser.h"
#include "ConsoleCommand.h"

class Console
{
public:
	Console() = default;
	Console(const Console& rhs) = default;
	~Console() = default;

	Console& operator=(const Console& rhs) = default;

	void ExecuteCommand(const std::string& command);

	ColoredLines GetPrompt() const;

	void WriteLine(const std::string& message);

	const std::string& GetCurrentDirectory() const;
	void SetCurrentDirectory(const std::string& value);

	void OpenProject(const std::string& fullPath);
	void Exit();

private:
	bool Execute(
		std::tuple<>,
		const ConsoleCommandParser& parsedCommand);
	template <typename Command, typename... Commands>
	bool Execute(
		std::tuple<Command, Commands...>,
		const ConsoleCommandParser& parsedCommand)
	{
		Command command;
		if (command.GetName() != parsedCommand.GetName())
			return Execute(std::tuple<Commands...>{}, parsedCommand);
		command.Execute(*this, parsedCommand.GetArguments());
		return true;
	}

	std::vector<ConsoleCommand> GetCommands(std::tuple<>) const;
	template <typename Command, typename... Commands>
	std::vector<ConsoleCommand> GetCommands(std::tuple<Command, Commands...>) const
	{
		std::vector<ConsoleCommand> commands;
		commands.push_back(Command{});
		for (const auto& command : GetCommands(std::tuple<Commands...>{}))
			commands.push_back(command);
		return commands;
	}

private:
	friend class ConsoleTest;
	std::string errorCommand;
	std::string errorMessage;
	std::string currentDirectory = R"(c:\save\code)";
	std::vector<std::string> messages;
};

