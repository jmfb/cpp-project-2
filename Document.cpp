#include "Document.h"
#include <Wex/Exception.h>
#include <fstream>

void Document::Open(const std::string& fileName)
{
	lines.clear();
	std::ifstream in{ fileName.c_str() };
	std::string line;
	while (std::getline(in, line))
		lines.push_back(line);
	lines.push_back({});
}

int Document::GetLineCount() const
{
	return lines.size();
}

const std::string& Document::GetLine(int lineNumber) const
{
	CheckError(lineNumber < 0, 0, "Line number must be greater than or equal to zero.");
	CheckError(lineNumber >= static_cast<int>(lines.size()), 0, "Line number must be less than line count.");
	return lines[lineNumber];
}

