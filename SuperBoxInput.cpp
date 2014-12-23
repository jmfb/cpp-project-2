#include <Wex/WindowsInclude.h>
#include "SuperBoxInput.h"
#include <Wex/ClientDeviceContext.h>
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "ColorScheme.h"

SuperBoxInput::SuperBoxInput(SuperBoxInputEvents& events)
	: events{ &events }
{
}

void SuperBoxInput::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "SuperBoxInput";
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.style = CS_HREDRAW|CS_VREDRAW;
}

bool SuperBoxInput::OnCreate(CREATESTRUCT* cs)
{
	Wex::ClientDeviceContext deviceContext{ GetHandle() };
	font.Create("Consolas", Wex::Font::CalculateHeight(deviceContext, 10));
	deviceContext.Select(font);
	textSize = deviceContext.GetTextSize();
	return true;
}

void SuperBoxInput::OnPaint()
{
	Wex::PaintDeviceContext paintDeviceContext{ GetHandle() };
	Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
	auto client = GetClient();
	deviceContext.FillSolidRect(client, ColorScheme::Background::Default);
	deviceContext.Select(font);
	deviceContext.SetTextColor(ColorScheme::Console::Default);
	deviceContext.SetBackColor(ColorScheme::Background::Default);
	deviceContext.DrawText(value, client);
	if (::GetFocus() == GetHandle())
		::SetCaretPos(textSize.cx * value.size(), 0);
}

void SuperBoxInput::OnChar(int c, int count, unsigned long flags)
{
	if (c == VK_RETURN)
		events->OnOpenSelection();
	else if (c == VK_ESCAPE)
		events->OnCancelSearch();
	else if (c == VK_BACK)
	{
		if (!value.empty())
		{
			value.erase(value.begin() + value.size() - 1);
			events->OnUpdateFilter(value);
			Invalidate(false);
		}
	}
	else if (std::isprint(static_cast<char>(c)))
	{
		value += static_cast<char>(c);
		events->OnUpdateFilter(value);
		Invalidate(false);
	}
}

void SuperBoxInput::OnKeyDown(int c, int count, unsigned long flags)
{
	if (c == VK_UP)
		events->OnSelectPrevious();
	else if (c == VK_DOWN)
		events->OnSelectNext();
}

void SuperBoxInput::OnSetFocus(HWND hwnd)
{
	CreateSolidCaret(2, textSize.cy);
	::SetCaretPos(textSize.cx * value.size(), 0);
	ShowCaret();
}

void SuperBoxInput::OnKillFocus(HWND hwnd)
{
	::DestroyCaret();
}

