#include <Wex/WindowsInclude.h>
#include "ConsoleDirectoryList.h"
#include <Wex/Path.h>
#include <Wex/WindowsException.h>
#include <stdexcept>

ConsoleDirectoryList::ConsoleDirectoryList()
	: ConsoleCommand{ "dir", { "filter" }, "Directory listing." }
{
}

void ConsoleDirectoryList::Execute(
	Console& console,
	const std::vector<std::string>& arguments)
{
	auto filter = arguments.empty() ? "*" : arguments[0];
	auto fullPath = Wex::Path::Combine(console.GetCurrentDirectory(), filter);
	WIN32_FIND_DATA data;
	auto result = ::FindFirstFile(fullPath.c_str(), &data);
	if (result == INVALID_HANDLE_VALUE)
	{
		auto lastError = ::GetLastError();
		if (lastError == ERROR_FILE_NOT_FOUND ||
			lastError == ERROR_PATH_NOT_FOUND ||
			lastError == ERROR_NO_MORE_FILES)
			console.WriteLine("No files found.");
		else
			throw std::runtime_error{ Wex::WindowsException::FormatMessage(lastError) };
		return;
	}

	do
	{
		std::string fileName = data.cFileName;
		if (fileName == "." || fileName == "..")
			continue;
		console.WriteLine(data.cFileName);
	}
	while (::FindNextFile(result, &data));
	::FindClose(result);
}

