#include <Wex/WindowsInclude.h>
#include "DocumentView.h"

DocumentView::DocumentView(const std::string& fullPath)
{
	Open(fullPath);
}

void DocumentView::Open(const std::string& fullPath)
{
	firstVisibleLine = 0;
	document.Open(fullPath);
}

bool DocumentView::IsFor(const std::string& fullPath) const
{
	return document.Is(fullPath);
}

const std::string& DocumentView::GetTitle() const
{
	return document.GetFileName();
}

void DocumentView::SetViewSize(int visibleLineCount)
{
	this->visibleLineCount = visibleLineCount;
}

int DocumentView::GetLineCount() const
{
	auto remainingLines = document.GetLineCount() - firstVisibleLine;
	return std::min(remainingLines, visibleLineCount + 1);
}

const std::string& DocumentView::GetLine(int lineNumber) const
{
	return document.GetLine(lineNumber + firstVisibleLine);
}

void DocumentView::PageDown()
{
	auto pageDownLine = firstVisibleLine + visibleLineCount;
	if (pageDownLine >= document.GetLineCount())
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

