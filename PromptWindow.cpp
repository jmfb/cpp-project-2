#include <Wex/WindowsInclude.h>
#include "PromptWindow.h"
#include <Wex/ClientDeviceContext.h>
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "ColorScheme.h"

PromptWindow::PromptWindow(PromptWindowEvents& events)
	: events(&events)
{
}

void PromptWindow::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "PromptWindow";
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.style = CS_HREDRAW|CS_VREDRAW;
}

bool PromptWindow::OnCreate(CREATESTRUCT* cs)
{
	Wex::ClientDeviceContext deviceContext{ GetHandle() };
	font.Create("Consolas", Wex::Font::CalculateHeight(deviceContext, 10));
	deviceContext.Select(font);
	textSize = deviceContext.GetTextSize();
	CreateSolidCaret(2, textSize.cy);
	::SetCaretPos(0, 0);
	ShowCaret();
	return true;
}

void PromptWindow::OnPaint()
{
	Wex::PaintDeviceContext paintDeviceContext{ GetHandle() };
	Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
	auto client = GetClient();
	deviceContext.FillSolidRect(client, ColorScheme::Background::Default);
	deviceContext.Select(font);
	deviceContext.SetTextColor(ColorScheme::Console::Default);
	deviceContext.SetBackColor(ColorScheme::Background::Default);

	auto promptRect = client;
	promptRect.right = textSize.cx * prompt.size();
	deviceContext.DrawText(prompt, promptRect);
	auto commandRect = client - promptRect;
	deviceContext.DrawText(command, commandRect);
	::SetCaretPos(textSize.cx * (prompt.size() + command.size()), 0);
}

void PromptWindow::OnChar(int c, int count, unsigned long flags)
{
	if (c == VK_RETURN)
	{
		events->OnExecuteCommand(command);
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
		if (std::isprint(static_cast<char>(c)))
			command += static_cast<char>(c);
	}
	Invalidate(false);
}

void PromptWindow::SetPrompt(const std::string& value)
{
	prompt = value;
	Invalidate(false);
}

