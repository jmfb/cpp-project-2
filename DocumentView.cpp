#include <Wex/WindowsInclude.h>
#include "DocumentView.h"

void DocumentView::SetDocument(std::shared_ptr<Document> document)
{
	firstVisibleLine = 0;
	this->document = document;
}

void DocumentView::SetViewSize(int visibleLineCount)
{
	this->visibleLineCount = visibleLineCount;
}

int DocumentView::GetLineCount() const
{
	if (!document)
		return 0;
	auto remainingLines = document->GetLineCount() - firstVisibleLine;
	return std::min(remainingLines, visibleLineCount + 1);
}

const std::string& DocumentView::GetLine(int lineNumber) const
{
	return document->GetLine(lineNumber + firstVisibleLine);
}

void DocumentView::PageDown()
{
	auto pageDownLine = firstVisibleLine + visibleLineCount;
	if (pageDownLine >= document->GetLineCount())
		return;
	firstVisibleLine = pageDownLine;
}

void DocumentView::PageUp()
{
	auto pageUpLine = firstVisibleLine - visibleLineCount;
	if (pageUpLine < 0)
		pageUpLine = 0;
	firstVisibleLine = pageUpLine;
}

