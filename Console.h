#pragma once
#include <vector>
#include <string>
#include "ColoredText.h"
#include "ConsoleCommandParser.h"
#include "ConsoleCommand.h"
#include "ConsoleEvents.h"
#include <functional>

class Console
{
public:
	Console(ConsoleEvents& events);
	Console(const Console& rhs) = default;
	~Console() = default;

	Console& operator=(const Console& rhs) = default;

	class ConsoleMode
	{
	public:
		std::function<bool(Console&,const ConsoleCommandParser&)> executeCommand;
		std::function<std::vector<ConsoleCommand>()> getCommands;
		std::function<std::string(const Console&)> getPrompt;

		template <typename Commands>
		static ConsoleMode Create(std::function<std::string(const Console&)> getPrompt)
		{
			return
			{
				[](Console& console, const ConsoleCommandParser& parsedCommand)
				{
					return Execute(
						Commands{},
						console,
						parsedCommand);
				},
				[]{ return GetCommands(Commands{}); },
				getPrompt
			};
		}

	private:
		static bool Execute(
			std::tuple<>,
			Console& console,
			const ConsoleCommandParser& parsedCommand);
		template <typename Command, typename... Commands>
		static bool Execute(
			std::tuple<Command, Commands...>,
			Console& console,
			const ConsoleCommandParser& parsedCommand)
		{
			Command command;
			if (command.GetName() != parsedCommand.GetName())
				return Execute(
					std::tuple<Commands...>{},
					console,
					parsedCommand);
			command.Execute(console, parsedCommand.GetArguments());
			return true;
		}
	
		static std::vector<ConsoleCommand> GetCommands(std::tuple<>);
		template <typename Command, typename... Commands>
		static std::vector<ConsoleCommand> GetCommands(std::tuple<Command, Commands...>)
		{
			std::vector<ConsoleCommand> commands;
			commands.push_back(Command{});
			for (const auto& command : GetCommands(std::tuple<Commands...>{}))
				commands.push_back(command);
			return commands;
		}
	};
	static const ConsoleMode Initial;
	static const ConsoleMode Project;

	void SwitchMode(const ConsoleMode& value);

	void ExecuteCommand(const std::string& command);

	std::string GetPrompt() const;
	ColoredLines GetDisplay() const;

	void WriteLine(const std::string& message);
	void WriteLine(const ColoredLine& message);

	const std::string& GetCurrentDirectory() const;
	void SetCurrentDirectory(const std::string& value);

	const std::string& GetCurrentProjectName() const;
	void SetCurrentProjectName(const std::string& value);

	void NewProject(const std::string& name);
	void OpenProject(const std::string& fullPath);
	void CloseProject();
	void Exit();

private:
	friend class ConsoleTest;
	ConsoleEvents* events = nullptr;
	const ConsoleMode* mode = nullptr;
	std::string errorCommand;
	std::string errorMessage;
	std::string currentDirectory = R"(c:\save\code)";
	std::string currentProjectName;
	std::vector<ColoredLine> messages;
};

