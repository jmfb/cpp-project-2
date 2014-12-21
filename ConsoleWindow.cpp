#include <Wex/WindowsInclude.h>
#include "ConsoleWindow.h"
#include <Wex/ClientDeviceContext.h>
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "ColorScheme.h"
#include "TextDrawer.h"

void ConsoleWindow::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "ConsoleWindow";
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.style = CS_HREDRAW|CS_VREDRAW;
}

bool ConsoleWindow::OnCreate(CREATESTRUCT* cs)
{
	Wex::ClientDeviceContext deviceContext{ GetHandle() };
	font.Create("Consolas", Wex::Font::CalculateHeight(deviceContext, 10));
	deviceContext.Select(font);
	textSize = deviceContext.GetTextSize();

	CreateSolidCaret(2, textSize.cy);
	::SetCaretPos(0, 0);
	ShowCaret();
	SetFocus();
	return true;
}

void ConsoleWindow::OnPaint()
{
	Wex::PaintDeviceContext paintDeviceContext{ GetHandle() };
	Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
	deviceContext.FillSolidRect(GetClient(), ColorScheme::Background::Default);
	deviceContext.Select(font);
	deviceContext.SetTextColor(ColorScheme::Console::Default);
	deviceContext.SetBackColor(ColorScheme::Background::Default);
	deviceContext.DrawText(command, GetClient());

	auto client = GetClient();
	TextDrawer drawer{ deviceContext };
	auto prompt = console.GetPrompt(command);
	for (auto lineNumber = 0ul; lineNumber < prompt.size(); ++lineNumber)
		drawer.DrawLine(client.left, client.right, lineNumber + 2, prompt[lineNumber]);
}

void ConsoleWindow::OnChar(int c, int count, unsigned long flags)
{
	if (c == VK_RETURN)
	{
		console.ExecuteCommand(command);
		command.clear();
	}
	else if (c == VK_BACK)
	{
		if (!command.empty())
			command.erase(command.begin() + command.size() - 1);
	}
	else if (c == VK_ESCAPE)
	{
		command.clear();
	}
	else
	{
		if (std::isprint(c))
			command.append(1, static_cast<char>(c));
	}
	::SetCaretPos(textSize.cx * command.size(), 0);
	Invalidate(false);
}

