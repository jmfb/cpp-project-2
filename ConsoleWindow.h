#pragma once
#include <Wex/CustomWindow.h>
#include <Wex/Font.h>
#include <Wex/Size.h>
#include "Console.h"

class ConsoleWindow : public Wex::CustomWindow<ConsoleWindow>
{
public:
	ConsoleWindow() = default;
	ConsoleWindow(const ConsoleWindow& rhs) = delete;
	~ConsoleWindow() = default;

	ConsoleWindow& operator=(const ConsoleWindow& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnPaint() override;
	void OnChar(int c, int count, unsigned long flags) override;

private:
	friend class ConsoleWindowTest;
	Wex::Font font;
	Wex::Size textSize;
	std::string command;
	Console console;
};

