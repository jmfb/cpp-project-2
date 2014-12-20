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

	void DrawLine(
		int left,
		int width,
		int lineNumber,
		const std::vector<ColoredText>& parts);

private:
	int GetCharacterColumns(int column, char character) const;
	void DrawCharacter(const Wex::Rect& rect, char character);
	void DrawSpace(const Wex::Rect& rect);
	void DrawTab(const Wex::Rect& rect);

private:
	Wex::DeviceContext& deviceContext;
	Wex::Size textSize;
};

