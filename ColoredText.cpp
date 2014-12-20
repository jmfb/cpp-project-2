#include <Wex/WindowsInclude.h>
#include "ColoredText.h"
#include "ColorScheme.h"

ColoredText::ColoredText(
	COLORREF textColor,
	COLORREF backColor,
	const std::string& text)
	: textColor(textColor), backColor(backColor), text(text)
{
}

ColoredText::ColoredText(
	COLORREF textColor,
	const std::string& text)
	: textColor(textColor),
	backColor(ColorScheme::Background::Default),
	text(text)
{
}

