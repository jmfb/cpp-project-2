#pragma once
#include <vector>
#include <string>
#include "ColoredText.h"

class CPlusPlusColorer
{
public:
	static std::vector<ColoredText> Color(const std::string& line);

private:
	static ColoredText ScanNextPart(
		const std::string& line,
		std::string::size_type index);
	static ColoredText ScanSpace(
		const std::string& line,
		std::string::size_type index);
	static ColoredText ScanWord(
		const std::string& line,
		std::string::size_type index);
	static ColoredText ScanPreProcessor(
		const std::string& line,
		std::string::size_type index);
	static ColoredText ScanPunctuation(
		const std::string& line,
		std::string::size_type index);
	static ColoredText ScanCharacter(
		const std::string& line,
		std::string::size_type index);
	static ColoredText ScanString(
		const std::string& line,
		std::string::size_type index);
	static ColoredText ScanNumber(
		const std::string& line,
		std::string::size_type index);

	static std::string::size_type SkipWhitespace(
		const std::string& line,
		std::string::size_type index);
	static std::string::size_type SkipIdentifier(
		const std::string& line,
		std::string::size_type index);

	static bool IsAfterInclude(
		const std::string& line,
		std::string::size_type index);

	static COLORREF GetWordColor(const std::string& word);
	static bool IsInstructionKeyword(const std::string& word);
	static bool IsTypeKeyword(const std::string& word);
};

