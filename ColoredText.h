#pragma once
#include <string>
#include <vector>

class ColoredText
{
public:
	ColoredText() = default;
	ColoredText(
		COLORREF textColor,
		COLORREF backColor,
		const std::string& text);
	ColoredText(
		COLORREF textColor,
		const std::string& text);
	ColoredText(const ColoredText& rhs) = default;
	~ColoredText() = default;

	ColoredText& operator=(const ColoredText& rhs) = default;

public:
	COLORREF textColor = 0;
	COLORREF backColor = 0;
	std::string text;
};

using ColoredLine = std::vector<ColoredText>;
using ColoredLines = std::vector<ColoredLine>;

