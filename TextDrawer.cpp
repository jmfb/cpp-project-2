#include <Wex/WindowsInclude.h>
#include "TextDrawer.h"
#include <Wex/Pen.h>
#include <Wex/Point.h>
#include "ColorScheme.h"

TextDrawer::TextDrawer(Wex::DeviceContext& deviceContext)
	: deviceContext(deviceContext)
{
	textSize = deviceContext.GetTextSize();
}

void TextDrawer::DrawLine(
	int left,
	int width,
	int lineNumber,
	const std::vector<ColoredText>& parts)
{
	auto top = lineNumber * textSize.cy;
	auto nextLeft = left;
	auto column = 0;
	for (const auto& part: parts)
	{
		deviceContext.SetBackColor(part.backColor);
		deviceContext.SetTextColor(part.textColor);
		for (auto character: part.text)
		{
			auto columns = GetCharacterColumns(column, character);
			auto characterWidth = columns * textSize.cx;
			Wex::Rect characterRect
			{
				Wex::Point{ nextLeft, top },
				Wex::Size{ characterWidth, textSize.cy }
			};
			DrawCharacter(characterRect, character);
			nextLeft += characterWidth;
			column += columns;
		}
	}
}

int TextDrawer::GetCharacterColumns(int column, char character) const
{
	if (character != '\t')
		return 1;
	return 4 - column % 4;
}

void TextDrawer::DrawCharacter(const Wex::Rect& rect, char character)
{
	if (character == ' ')
		DrawSpace(rect);
	else if (character == '\t')
		DrawTab(rect);
	else
		deviceContext.DrawText({ character, 1 }, rect);
}

void TextDrawer::DrawSpace(const Wex::Rect& rect)
{
	deviceContext.FillSolidRect(rect, deviceContext.GetBackColor());
	auto center = rect.GetCenter();
	deviceContext.FillSolidRect(
		Wex::Rect
		{
			Wex::Point{ center.x - 1, center.y - 1},
			Wex::Size{ 2, 2 }
		},
		ColorScheme::Text::Whitespace(deviceContext.GetTextColor()));
}

void TextDrawer::DrawTab(const Wex::Rect& rect)
{
	deviceContext.FillSolidRect(rect, deviceContext.GetBackColor());
	Wex::Pen pen{ PS_SOLID, 1, ColorScheme::Text::Whitespace(deviceContext.GetTextColor()) };
	deviceContext.Select(pen);
	auto center = rect.GetCenter().y - 1;
	auto tail = rect.left + 1;
	auto tip = tail + textSize.cx - 2;
	deviceContext.DrawLine({
		{ tail, center },
		{ tip, center },
		{ tip - 4, center - 4 }
	});
	deviceContext.DrawLine({
		{ tip, center },
		{ tip - 4, center + 4 }
	});
}

