#pragma once
#include "Document.h"

class DocumentView
{
public:
	DocumentView() = default;
	DocumentView(const std::string& fullPath);
	DocumentView(const DocumentView& rhs) = default;
	~DocumentView() = default;

	DocumentView& operator=(const DocumentView& rhs) = default;

	void Open(const std::string& fullPath);
	bool IsFor(const std::string& fullPath) const;
	const std::string& GetTitle() const;
	void SetViewSize(int visibleLineCount);
	int GetLineCount() const;
	const std::string& GetLine(int lineNumber) const;

	void PageDown();
	void PageUp();

private:
	friend class DocumentViewTest;
	Document document;
	int firstVisibleLine = 0;
	int visibleLineCount = 0;
};

