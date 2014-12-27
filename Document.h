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
	bool Is(const std::string& fileName) const;
	const std::string& GetFileName() const;

	int GetLineCount() const;
	const std::string& GetLine(int lineNumber) const;

private:
	friend class DocumentTest;
	std::string fileName;
	std::vector<std::string> lines;
};

