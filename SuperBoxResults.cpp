#include <Wex/WindowsInclude.h>
#include "SuperBoxResults.h"
#include <Wex/ClientDeviceContext.h>
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "ColorScheme.h"
#include "TextDrawer.h"

void SuperBoxResults::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "SuperBoxResults";
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.style = CS_HREDRAW|CS_VREDRAW;
}

bool SuperBoxResults::OnCreate(CREATESTRUCT* cs)
{
	Wex::ClientDeviceContext deviceContext{ GetHandle() };
	font.Create("Consolas", Wex::Font::CalculateHeight(deviceContext, 10));
	deviceContext.Select(font);
	textSize = deviceContext.GetTextSize();
	return true;
}

void SuperBoxResults::OnPaint()
{
	Wex::PaintDeviceContext paintDeviceContext{ GetHandle() };
	Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
	auto client = GetClient();
	deviceContext.FillSolidRect(client, ColorScheme::Background::Popup);
	deviceContext.Select(font);
	TextDrawer drawer{ deviceContext };
	auto lineNumber = 0;
	for (const auto& result : results)
	{
		auto background = lineNumber == selection ?
			ColorScheme::Background::SelectedLine :
			ColorScheme::Background::Popup;
		drawer.Fill(client.left, client.right, lineNumber, background);
		auto line = Colorize(result, background);
		drawer.DrawLine(client.left, client.right, lineNumber, line);
		++lineNumber;
	}
}

void SuperBoxResults::SetResults(
	const std::string& filter,
	const std::vector<std::string>& value)
{
	this->filter = filter;
	results = value;
	if (selection >= static_cast<int>(results.size()))
		selection = results.size() - 1;
	if (selection < 0)
		selection = 0;
	Invalidate(false);
}

void SuperBoxResults::SelectPrevious()
{
	if (selection > 0)
	{
		--selection;
		Invalidate(false);
	}
}

void SuperBoxResults::SelectNext()
{
	if ((selection + 1) < static_cast<int>(results.size()))
	{
		++selection;
		Invalidate(false);
	}
}

bool SuperBoxResults::HasSelection() const
{
	return selection >= 0 && selection < static_cast<int>(results.size());
}

const std::string& SuperBoxResults::GetSelection() const
{
	return results[selection];
}

ColoredLine SuperBoxResults::Colorize(const std::string& result, COLORREF background) const
{
	//TODO: fancy matching logic based on filter
	return
	{
		{ ColorScheme::Console::Default, background, result }
	};
}

