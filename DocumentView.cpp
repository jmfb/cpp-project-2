#include <Wex/WindowsInclude.h>
#include "DocumentView.h"
#include <Wex/ClientDeviceContext.h>
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "TextDrawer.h"
#include "CPlusPlusColorer.h"
#include "ColorScheme.h"

void DocumentView::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "DocumentView";
	windowClass.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_IBEAM);
}

bool DocumentView::OnCreate(CREATESTRUCT* cs)
{
	Wex::ClientDeviceContext deviceContext{ GetHandle() };
	font.Create("Consolas", Wex::Font::CalculateHeight(deviceContext, 10));
	return true;
}

void DocumentView::OnPaint()
{
	Wex::PaintDeviceContext paintDeviceContext{ GetHandle() };
	Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
	deviceContext.FillSolidRect(GetClient(), ColorScheme::Background::Default);

	auto document = weakDocument.lock();
	if (!document)
		return;

	deviceContext.Select(font);

	auto client = GetClient();
	TextDrawer drawer{ deviceContext };
	for (auto lineNumber = 0; lineNumber < document->GetLineCount(); ++lineNumber)
	{
		auto parts = CPlusPlusColorer::Color(document->GetLine(lineNumber));
		//TODO: modify for selection, find results, etc.
		drawer.DrawLine(client.left, client.right, lineNumber, parts);
	}
}

void DocumentView::SetDocument(std::weak_ptr<Document> value)
{
	weakDocument = value;
}

