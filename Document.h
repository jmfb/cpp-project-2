#pragma once
#include <vector>
#include <string>

class Document
{
public:
	Document() = default;
	Document(const Document& rhs) = default;
	~Document() = default;

	Document& operator=(const Document& rhs) = default;

	void Open(const std::string& fileName);

	int GetLineCount() const;
	const std::string& GetLine(int lineNumber) const;

private:
	friend class DocumentTest;
	std::vector<std::string> lines;
};

