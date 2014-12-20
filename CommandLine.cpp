#include "CommandLine.h"

CommandLine::CommandLine(int argc, const char* argv[])
{
	ParseArguments(argc, argv);
}

bool CommandLine::GetFlag(const std::string& name) const
{
	return flags.find(name) != flags.end();
}

std::string CommandLine::GetSetting(const std::string& name) const
{
	auto setting = settings.find(name);
	return setting == settings.end() ? "" : setting->second;
}

const std::vector<std::string>& CommandLine::GetTargets() const
{
	return targets;
}

void CommandLine::ParseArguments(int argc, const char* argv[])
{
	for (auto index = 0; index < argc; ++index)
		ParseArgument(argv[index]);
}

void CommandLine::ParseArgument(const std::string& argument)
{
	if (argument.empty())
		return;
	if (IsFlagOrSetting(argument))
		ParseFlagOrSetting(argument);
	else
		targets.push_back(argument);
}

bool CommandLine::IsFlagOrSetting(const std::string& argument)
{
	return argument[0] == '-' || argument[0] == '/';
}

void CommandLine::ParseFlagOrSetting(std::string argument)
{
	argument.erase(0, 1);
	if (argument.empty())
		return;
	if (IsSetting(argument))
		ParseSetting(argument);
	else
		flags.insert(argument);
}

bool CommandLine::IsSetting(const std::string& argument)
{
	return argument.find('=') != std::string::npos;
}

void CommandLine::ParseSetting(const std::string& argument)
{
	auto position = argument.find('=');
	auto key = argument.substr(0, position);
	std::string value;
	if (argument.size() > (position + 1))
		value = argument.substr(position + 1);
	settings[key] = value;
}

