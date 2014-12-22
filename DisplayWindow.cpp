#include <Wex/WindowsInclude.h>
#include "DisplayWindow.h"
#include <Wex/ClientDeviceContext.h>
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "TextDrawer.h"
#include "ColorScheme.h"

void DisplayWindow::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "DisplayWindow";
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.style = CS_HREDRAW|CS_VREDRAW;
}

bool DisplayWindow::OnCreate(CREATESTRUCT* cs)
{
	Wex::ClientDeviceContext deviceContext{ GetHandle() };
	font.Create("Consolas", Wex::Font::CalculateHeight(deviceContext, 10));
	return true;
}

void DisplayWindow::OnPaint()
{
	Wex::PaintDeviceContext paintDeviceContext{ GetHandle() };
	Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
	auto client = GetClient();
	deviceContext.FillSolidRect(client, ColorScheme::Background::Default);
	deviceContext.Select(font);
	TextDrawer drawer{ deviceContext };
	auto lineNumber = 0;
	for (const auto& line : lines)
		drawer.DrawLine(client.left, client.right, lineNumber++, line);
}

void DisplayWindow::SetLines(const ColoredLines& value)
{
	lines = value;
	Invalidate(false);
}

