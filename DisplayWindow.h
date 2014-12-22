#pragma once
#include <Wex/CustomWindow.h>
#include <Wex/Font.h>
#include "ColoredText.h"

class DisplayWindow : public Wex::CustomWindow<DisplayWindow>
{
public:
	DisplayWindow() = default;
	DisplayWindow(const DisplayWindow& rhs) = delete;
	~DisplayWindow() = default;

	DisplayWindow& operator=(const DisplayWindow& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnPaint() override;

	void SetLines(const ColoredLines& value);

private:
	friend class DisplayWindowTest;
	Wex::Font font;
	ColoredLines lines;
};

