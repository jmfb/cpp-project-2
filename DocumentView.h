#pragma once
#include "Document.h"
#include <memory>

class DocumentView
{
public:
	DocumentView() = default;
	DocumentView(const DocumentView& rhs) = default;
	~DocumentView() = default;

	DocumentView& operator=(const DocumentView& rhs) = default;

	void SetDocument(std::shared_ptr<Document> document);
	void SetViewSize(int visibleLineCount);
	int GetLineCount() const;
	const std::string& GetLine(int lineNumber) const;

	void PageDown();
	void PageUp();

private:
	friend class DocumentViewTest;
	std::shared_ptr<Document> document;
	int firstVisibleLine = 0;
	int visibleLineCount = 0;
};

