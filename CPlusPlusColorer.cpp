#include <Wex/WindowsInclude.h>
#include "CPlusPlusColorer.h"
#include "ColorScheme.h"
#include <cctype>
#include <set>

std::vector<ColoredText> CPlusPlusColorer::Color(const std::string& line)
{
	std::vector<ColoredText> parts;
	std::string::size_type index = 0;
	while (index < line.size())
	{
		auto part = ScanNextPart(line, index);
		parts.push_back(part);
		index += part.text.size();
	}
	return parts;
}

ColoredText CPlusPlusColorer::ScanNextPart(
	const std::string& line,
	std::string::size_type index)
{
	if (IsAfterInclude(line, index))
		return
		{
			ColorScheme::CPlusPlus::String,
			ColorScheme::Background::Default,
			line.substr(index)
		};

	auto c = line[index];
	if (std::isspace(c))
		return ScanSpace(line, index);
	if (std::isalpha(c) || c == '_')
		return ScanWord(line, index);
	if (c == '#')
		return ScanPreProcessor(line, index);
	if (c == '\'')
		return ScanCharacter(line, index);
	if (c == '"')
		return ScanString(line, index);
	if (std::ispunct(c))
		return ScanPunctuation(line, index);
	if (std::isdigit(c))
		return ScanNumber(line, index);

	return
	{
		ColorScheme::Text::Default,
		ColorScheme::Background::Default,
		line.substr(index, 1)
	};
}

ColoredText CPlusPlusColorer::ScanSpace(
	const std::string& line,
	std::string::size_type index)
{
	auto end = SkipWhitespace(line, index + 1);
	return
	{
		ColorScheme::Text::Default,
		ColorScheme::Background::Default,
		line.substr(index, end - index)
	};
}

ColoredText CPlusPlusColorer::ScanWord(
	const std::string& line,
	std::string::size_type index)
{
	auto end = SkipIdentifier(line, index + 1);
	auto word = line.substr(index, end - index);
	return
	{
		GetWordColor(word),
		ColorScheme::Background::Default,
		word
	};
}

ColoredText CPlusPlusColorer::ScanPreProcessor(
	const std::string& line,
	std::string::size_type index)
{
	auto end = SkipWhitespace(line, index + 1);
	end = SkipIdentifier(line, end);
	return
	{
		ColorScheme::CPlusPlus::PreProcessor,
		ColorScheme::Background::Default,
		line.substr(index, end - index)
	};
}

ColoredText CPlusPlusColorer::ScanPunctuation(
	const std::string& line,
	std::string::size_type index)
{
	if (line[index] == '/' &&
		(index + 1) < line.size() &&
		line[index + 1] == '/')
		return
		{
			ColorScheme::CPlusPlus::Comment,
			ColorScheme::Background::Default,
			line.substr(index)
		};
	return
	{
		ColorScheme::CPlusPlus::Punctuation,
		ColorScheme::Background::Default,
		line.substr(index, 1)
	};
}

ColoredText CPlusPlusColorer::ScanCharacter(
	const std::string& line,
	std::string::size_type index)
{
	auto end = index + 1;
	for (; end < line.size(); ++end)
	{
		auto c = line[end];
		if (c == '\\' && (end + 1 < line.size()))
		{
			++end;
			continue;
		}
		if (c == '\'')
		{
			++end;
			break;
		}
	}
	return
	{
		ColorScheme::CPlusPlus::String,
		ColorScheme::Background::Default,
		line.substr(index, end - index)
	};
}

ColoredText CPlusPlusColorer::ScanString(
	const std::string& line,
	std::string::size_type index)
{
	//TODO: Check for raw-string R"(...)"
	auto end = index + 1;
	for (; end < line.size(); ++end)
	{
		auto c = line[end];
		if (c == '\\' && (end + 1 < line.size()))
		{
			++end;
			continue;
		}
		if (c == '"')
		{
			++end;
			break;
		}
	}
	return
	{
		ColorScheme::CPlusPlus::String,
		ColorScheme::Background::Default,
		line.substr(index, end - index)
	};
}

ColoredText CPlusPlusColorer::ScanNumber(
	const std::string& line,
	std::string::size_type index)
{
	auto end = index + 1;
	for (; end < line.size(); ++end)
	{
		auto c = line[end];
		if (std::isalnum(c) || c == '.')
			continue;
		break;
	}
	return
	{
		ColorScheme::CPlusPlus::Number,
		ColorScheme::Background::Default,
		line.substr(index, end - index)
	};
}

std::string::size_type CPlusPlusColorer::SkipWhitespace(
	const std::string& line,
	std::string::size_type index)
{
	for (auto end = index; end < line.size(); ++end)
	{
		auto c = line[end];
		if (std::isspace(c))
			continue;
		return end;
	}
	return line.size();
}

std::string::size_type CPlusPlusColorer::SkipIdentifier(
	const std::string& line,
	std::string::size_type index)
{
	for (auto end = index; end < line.size(); ++end)
	{
		auto c = line[end];
		if (std::isalnum(c) || c == '_')
			continue;
		return end;
	}
	return line.size();
}

bool CPlusPlusColorer::IsAfterInclude(
	const std::string& line,
	std::string::size_type index)
{
	auto firstNonSpace = SkipWhitespace(line, 0);
	auto isPreProcessor =
		firstNonSpace < line.size() &&
		line[firstNonSpace] == '#';
	if (!isPreProcessor)
		return false;
	auto startOfDirective = SkipWhitespace(line, firstNonSpace + 1);
	auto endOfDirective = SkipIdentifier(line, startOfDirective + 1);
	if (startOfDirective >= line.size())
		return false;
	auto directive = line.substr(
		startOfDirective,
		endOfDirective - startOfDirective);
	if (directive != "include")
		return false;
	return index >= SkipWhitespace(line, endOfDirective + 1);
}

COLORREF CPlusPlusColorer::GetWordColor(const std::string& word)
{
	if (IsInstructionKeyword(word))
		return ColorScheme::CPlusPlus::InstructionKeyword;
	if (IsTypeKeyword(word))
		return ColorScheme::CPlusPlus::TypeKeyword;
	if (word == "Wex" ||
		word == "std") //TODO: context sensitive namespace
		return ColorScheme::CPlusPlus::Namespace;
	#if 0
	if (word == "MainFrame" ||
		word == "WNDCLASSEX" ||
		word == "CREATESTRUCT" ||
		word == "Document" ||
		word == "Size") //TODO: context sensitive class
		return ColorScheme::CPlusPlus::Class;
	if (word == "CS_DBLCLKS" ||
		word == "CS_HREDRAW" ||
		word == "CS_VREDRAW" ||
		word == "IDC_ARROW" ||
		word == "WS_CHILD" ||
		word == "WS_VISIBLE" ||
		word == "WS_CLIPSIBLINGS" ||
		word == "WS_CLIPCHILDREN") //TODO: context sensitive macro
		return ColorScheme::CPlusPlus::Macro;
	if (word == "windowClass" ||
		word == "cs" ||
		word == "type" ||
		word == "size") //TODO: context sensitive parameter
		return ColorScheme::CPlusPlus::Parameter;
	#endif
	return ColorScheme::CPlusPlus::Identifier;
}

bool CPlusPlusColorer::IsInstructionKeyword(const std::string& word)
{
	static const std::set<std::string> keywords
	{
		"namespace", "using",
		"class", "struct", "union", "enum",
		"public", "protected", "private",
		"virtual", "override", "final",
		"typedef", "template", "typename",
		"decltype",
		"static", "friend", "inline", "extern",
		"constexpr", "__declspec", "dllexport",
		"if", "else", "for", "do", "while", "switch",
		"case", "break", "continue", "default", "return", "goto",
		"operator", "new", "delete", "typeid", "sizeof",
		"__stdcall",
		"const_cast", "static_cast", "dynamic_cast", "reinterpret_cast",
		"this", "true", "false", "nullptr",
		"try", "catch", "throw",
		"static_assert",
		"noexcept"
	};
	return keywords.find(word) != keywords.end();
}

bool CPlusPlusColorer::IsTypeKeyword(const std::string& word)
{
	static const std::set<std::string> keywords
	{
		"void", "bool", "short", "long", "int",
		"signed", "unsigned",
		"float", "double",
		"const", "volatile",
		"register", "auto",
		"char", "wchar_t"
	};
	return keywords.find(word) != keywords.end();
}

