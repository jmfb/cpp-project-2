#include <Wex/WindowsInclude.h>
#include "DocumentWindow.h"
#include <Wex/ClientDeviceContext.h>
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "TextDrawer.h"
#include "CPlusPlusColorer.h"
#include "ColorScheme.h"
#include "resource.h"

DocumentWindow::DocumentWindow()
{
	HandleCommand(ID_PAGE_DOWN, &DocumentWindow::OnPageDown);
	HandleCommand(ID_PAGE_UP, &DocumentWindow::OnPageUp);
}

void DocumentWindow::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "DocumentWindow";
	windowClass.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_IBEAM);
}

bool DocumentWindow::OnCreate(CREATESTRUCT* cs)
{
	Wex::ClientDeviceContext deviceContext{ GetHandle() };
	font.Create("Consolas", Wex::Font::CalculateHeight(deviceContext, 10));
	deviceContext.Select(font);
	textSize = deviceContext.GetTextSize();
	return true;
}

void DocumentWindow::OnPaint()
{
	Wex::PaintDeviceContext paintDeviceContext{ GetHandle() };
	Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
	deviceContext.FillSolidRect(GetClient(), ColorScheme::Background::Default);
	deviceContext.Select(font);
	auto client = GetClient();
	TextDrawer drawer{ deviceContext };
	for (auto lineNumber = 0; lineNumber < documentView.GetLineCount(); ++lineNumber)
	{
		auto parts = CPlusPlusColorer::Color(documentView.GetLine(lineNumber));
		//TODO: modify for selection, find results, etc.
		drawer.DrawLine(client.left, client.right, lineNumber, parts);
	}
}

void DocumentWindow::OnSize(int type, const Wex::Size& size)
{
	auto clientHeight = GetClient().GetHeight();
	auto visibleLineCount = clientHeight / textSize.cy;
	documentView.SetViewSize(visibleLineCount);
}

void DocumentWindow::OnPageDown()
{
	documentView.PageDown();
	Invalidate(false);
}

void DocumentWindow::OnPageUp()
{
	documentView.PageUp();
	Invalidate(false);
}

void DocumentWindow::SetDocument(std::shared_ptr<Document> value)
{
	documentView.SetDocument(value);
}

