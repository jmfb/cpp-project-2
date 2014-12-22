#pragma once
#include "ConsoleCommand.h"
#include "Console.h"

class ConsoleDirectoryList : public ConsoleCommand
{
public:
	ConsoleDirectoryList();
	ConsoleDirectoryList(const ConsoleDirectoryList& rhs) = default;
	~ConsoleDirectoryList() = default;

	ConsoleDirectoryList& operator=(const ConsoleDirectoryList& rhs) = default;

	void Execute(Console& console, const std::vector<std::string>& arguments);

private:

private:
	friend class ConsoleDirectoryListTest;
};

