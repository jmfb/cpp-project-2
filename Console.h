#pragma once
#include <vector>
#include <string>
#include "ColoredText.h"

class Console
{
public:
	Console() = default;
	Console(const Console& rhs) = default;
	~Console() = default;

	Console& operator=(const Console& rhs) = default;

	void ExecuteCommand(const std::string& command);

	std::vector<std::vector<ColoredText>> GetPrompt(
		const std::string& partialCommand) const;

private:
	friend class ConsoleTest;
	std::string errorCommand;
	std::string errorMessage;
};

