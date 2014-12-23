#pragma once
#include <Wex/DeviceContext.h>
#include <Wex/Rect.h>
#include <Wex/Size.h>
#include <vector>
#include "ColoredText.h"

class TextDrawer
{
public:
	TextDrawer(Wex::DeviceContext& deviceContext);
	TextDrawer(const TextDrawer& rhs) = delete;
	~TextDrawer() = default;

	TextDrawer& operator=(const TextDrawer& rhs) = delete;

	void Fill(int left, int width, int lineNumber, COLORREF color);
	void DrawLine(
		int left,
		int right,
		int lineNumber,
		const ColoredLine& line);

private:
	int GetCharacterColumns(int column, char character) const;
	void DrawCharacter(const Wex::Rect& rect, char character);
	void DrawSpace(const Wex::Rect& rect);
	void DrawTab(const Wex::Rect& rect);

private:
	Wex::DeviceContext& deviceContext;
	Wex::Size textSize;
};

