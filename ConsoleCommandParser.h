#pragma once
#include <string>
#include <vector>

class ConsoleCommandParser
{
public:
	ConsoleCommandParser() = default;
	ConsoleCommandParser(const std::string& command);
	ConsoleCommandParser(const ConsoleCommandParser& rhs) = default;
	~ConsoleCommandParser() = default;

	ConsoleCommandParser& operator=(const ConsoleCommandParser& rhs) = default;

	const std::string& GetName() const;
	const std::vector<std::string>& GetArguments() const;

private:
	friend class ConsoleCommandParserTest;
	std::string name;
	std::vector<std::string> arguments;
};

