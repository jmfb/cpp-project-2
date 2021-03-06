#pragma once

namespace ColorScheme
{
	namespace Background
	{
		static const auto Default = RGB(20, 20, 20);
		static const auto SelectedLine = RGB(64, 64, 64);
		static const auto Margin = RGB(51, 51, 51);
		static const auto SelectedText = RGB(51, 153, 255);
		static const auto MatchingText = RGB(119, 56, 0);
		static const auto Popup = RGB(0, 0, 0);
	}

	namespace Text
	{
		static const auto Default = RGB(50, 180, 205);
		static const auto Selected = RGB(0, 0, 0);
		static const auto LineNumber = RGB(43, 145, 175);

		COLORREF Whitespace(COLORREF color);
	}

	namespace Console
	{
		static const auto Default = RGB(200, 200, 200);
		static const auto Command = RGB(86, 156, 214);
		static const auto Comment = RGB(87, 166, 74);
		static const auto String = RGB(214, 157, 133);
		static const auto Error = RGB(220, 0, 0);
		static const auto Directory = RGB(0, 255, 0);
		static const auto Project = RGB(189, 99, 197);
	}

	namespace SuperBox
	{
		static const auto Match = RGB(189, 99, 197);
		static const auto Directory = RGB(87, 166, 74);
		static const auto Extension = RGB(140, 140, 140);
		static const auto File = RGB(220, 220, 220);
	}

	namespace CPlusPlus
	{
		static const auto Comment = RGB(87, 166, 74);
		static const auto String = RGB(214, 157, 133);
		static const auto Punctuation = RGB(220, 220, 220);
		static const auto Number = RGB(181, 206, 168);
		static const auto InstructionKeyword = RGB(86, 156, 214);
		static const auto TypeKeyword = RGB(184, 215, 163);
		static const auto Identifier = RGB(200, 200, 200);
		static const auto PreProcessor = RGB(155, 155, 155);
		static const auto Class = RGB(78, 201, 176);
		static const auto Namespace = RGB(82, 178, 195);
		static const auto Parameter = RGB(127, 127, 127);
		static const auto Macro = RGB(189, 99, 197);
	}
}

