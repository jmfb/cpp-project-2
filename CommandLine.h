#pragma once
#include <vector>
#include <string>
#include <set>
#include <map>

class CommandLine
{
public:
	CommandLine() = default;
	CommandLine(int argc, const char* argv[]);
	CommandLine(const CommandLine& rhs) = default;
	~CommandLine() = default;

	CommandLine& operator=(const CommandLine& rhs) = default;

	bool GetFlag(const std::string& name) const;
	std::string GetSetting(const std::string& name) const;
	const std::vector<std::string>& GetTargets() const;

private:
	void ParseArguments(int argc, const char* argv[]);
	void ParseArgument(const std::string& argument);
	static bool IsFlagOrSetting(const std::string& argument);
	void ParseFlagOrSetting(std::string argument);
	static bool IsSetting(const std::string& argument);
	void ParseSetting(const std::string& argument);

private:
	friend class CommandLineTest;
	std::set<std::string> flags;
	std::map<std::string, std::string> settings;
	std::vector<std::string> targets;
};

