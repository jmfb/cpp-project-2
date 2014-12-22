#pragma once
#include <Wex/CustomWindow.h>
#include "PromptWindow.h"
#include "DisplayWindow.h"
#include "Console.h"

class ConsoleWindow :
	public Wex::CustomWindow<ConsoleWindow>,
	public PromptWindowEvents
{
public:
	ConsoleWindow();
	ConsoleWindow(const ConsoleWindow& rhs) = delete;
	~ConsoleWindow() = default;

	ConsoleWindow& operator=(const ConsoleWindow& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnSetFocus(HWND hwnd) override;
	void OnSize(int type, const Wex::Size& size) override;

	void OnExecuteCommand(const std::string& command) override;

private:
	friend class ConsoleWindowTest;
	PromptWindow promptWindow;
	DisplayWindow displayWindow;
	Console console;
};

