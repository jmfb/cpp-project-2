#include "ConsoleCommandParser.h"
#include <sstream>

ConsoleCommandParser::ConsoleCommandParser(const std::string& command)
{
	std::istringstream in{ command };
	in >> name;
	while (in)
	{
		std::string argument;
		in >> std::ws;
		if (in.peek() == '"')
		{
			in.get();
			std::getline(in, argument, '"');
		}
		else
		{
			in >> argument;
		}
		if (!argument.empty())
			arguments.push_back(argument);
	}
}

const std::string& ConsoleCommandParser::GetName() const
{
	return name;
}

const std::vector<std::string>& ConsoleCommandParser::GetArguments() const
{
	return arguments;
}

