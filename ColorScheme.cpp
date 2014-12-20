#include <Wex/WindowsInclude.h>
#include "ColorScheme.h"

COLORREF ColorScheme::Text::Whitespace(COLORREF color)
{
	auto darken = [](int component){ return (component * 4) / 10; };
	return RGB(
		darken(GetRValue(color)),
		darken(GetGValue(color)),
		darken(GetBValue(color)));
}

