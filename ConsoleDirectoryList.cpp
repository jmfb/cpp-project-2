#include <Wex/WindowsInclude.h>
#include "ConsoleDirectoryList.h"
#include <Wex/Directory.h>
#include <Wex/Path.h>
#include <Wex/File.h>
#include <Wex/String.h>
#include <array>
#include "ColorScheme.h"
#include "Project.h"

ConsoleDirectoryList::ConsoleDirectoryList()
	: ConsoleCommand{ "dir", { "filter" }, "Directory listing." }
{
}

void ConsoleDirectoryList::Execute(
	Console& console,
	const std::vector<std::string>& arguments)
{
	auto filter = arguments.empty() ? "*" : arguments[0];
	auto directory = console.GetCurrentDirectory();
	auto results = Wex::Directory::Find(directory, filter);
	const auto columnCount = 4;
	std::array<int, columnCount> columnWidths;
	for (auto& columnWidth : columnWidths)
		columnWidth = 0;
	auto lineCount = (results.size() + columnCount - 1) / columnCount;
	std::vector<std::array<Wex::FileInfo, columnCount>> lines(lineCount);
	for (auto lineNumber = 0ul; lineNumber < lineCount; ++lineNumber)
	{
		for (auto column = 0; column < columnCount; ++column)
		{
			auto index = column * lineCount + lineNumber;
			if (index >= results.size())
				break;
			const auto& fileInfo = results[index];
			auto fileName = fileInfo.GetFileName();
			columnWidths[column] = std::max(
				columnWidths[column],
				static_cast<int>(fileName.size()));
			lines[lineNumber][column] = fileInfo;
		}
	}
	for (const auto& line : lines)
	{
		ColoredLine coloredLine;
		for (auto column = 0; column < columnCount; ++column)
		{
			const auto& fileInfo = line[column];
			const auto& fileName = fileInfo.GetFileName();
			if (fileName.empty())
				continue;
			auto name = Wex::String::PadRight(fileName, columnWidths[column] + 5);
			auto color = ColorScheme::Console::Default;
			if (fileInfo.IsDirectory())
			{
				color = ColorScheme::Console::Directory;
				auto projectFile = Wex::Path::Combine(
					directory,
					fileName,
					fileName + "." + Project::Extension);
				if (Wex::File::Exists(projectFile))
					color = ColorScheme::Console::Project;
			}
			else if (fileInfo.GetExtension() == Project::Extension)
				color = ColorScheme::Console::Project;
			coloredLine.emplace_back(color, name);
		}
		console.WriteLine(coloredLine);
	}
}

