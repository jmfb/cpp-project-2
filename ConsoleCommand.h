#pragma once
#include <string>
#include <vector>
#include "ColoredText.h"

class ConsoleCommand
{
public:
	ConsoleCommand() = default;
	ConsoleCommand(
		const std::string& name,
		const std::vector<std::string>& arguments,
		const std::string& description);
	ConsoleCommand(const ConsoleCommand& rhs) = default;
	~ConsoleCommand() = default;

	ConsoleCommand& operator=(const ConsoleCommand& rhs) = default;

	const std::string& GetName() const;
	const std::vector<std::string>& GetArguments() const;
	const std::string& GetDescription() const;

	int GetCommandLength() const;
	ColoredLine GetPrompt(int descriptionColumn) const;

protected:
	void ValidateArguments(const std::vector<std::string>& value) const;
	
private:
	friend class ConsoleCommandTest;
	std::string name;
	std::vector<std::string> arguments;
	std::string description;
};

