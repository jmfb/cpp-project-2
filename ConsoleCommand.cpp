#include <Wex/WindowsInclude.h>
#include "ConsoleCommand.h"
#include "ColorScheme.h"
#include <stdexcept>

ConsoleCommand::ConsoleCommand(
	const std::string& name,
	const std::vector<std::string>& arguments,
	const std::string& description)
	: name(name), arguments(arguments), description(description)
{
}

const std::string& ConsoleCommand::GetName() const
{
	return name;
}

const std::vector<std::string>& ConsoleCommand::GetArguments() const
{
	return arguments;
}

const std::string& ConsoleCommand::GetDescription() const
{
	return description;
}

int ConsoleCommand::GetCommandLength() const
{
	auto commandLength = name.size();
	for (const auto& argument : arguments)
		commandLength += argument.size() + 1;
	return commandLength;
}

ColoredLine ConsoleCommand::GetPrompt(int descriptionColumn) const
{
	ColoredLine line{ { ColorScheme::Console::Command, name } };
	for (const auto& argument : arguments)
	{
		line.emplace_back(ColorScheme::Text::Default, " ");
		line.emplace_back(ColorScheme::Console::String, argument);
	}
	auto commandLength = GetCommandLength();
	auto paddingLength = commandLength < descriptionColumn ?
		descriptionColumn - commandLength :
		1;
	line.emplace_back(ColorScheme::Text::Default, std::string(paddingLength, ' '));
	line.emplace_back(ColorScheme::Console::Comment, "//" + description);
	return line;
}

void ConsoleCommand::ValidateArguments(const std::vector<std::string>& value) const
{
	if (value.size() != arguments.size())
		throw std::runtime_error{ "Incorrect number of arguments." };
}

