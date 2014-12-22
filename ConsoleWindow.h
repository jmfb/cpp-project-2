#pragma once
#include <Wex/CustomWindow.h>
#include "PromptWindow.h"
#include "DisplayWindow.h"
#include "Console.h"
#include "ConsoleWindowEvents.h"

class ConsoleWindow :
	public Wex::CustomWindow<ConsoleWindow>,
	public PromptWindowEvents,
	public ConsoleEvents
{
public:
	ConsoleWindow(ConsoleWindowEvents& events);
	ConsoleWindow(const ConsoleWindow& rhs) = delete;
	~ConsoleWindow() = default;

	ConsoleWindow& operator=(const ConsoleWindow& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnSetFocus(HWND hwnd) override;
	void OnSize(int type, const Wex::Size& size) override;

	void OnExecuteCommand(const std::string& command) override;

	void OnNewProject(const std::string& name) override;
	void OnOpenProject(const std::string& fullPath) override;
	void OnCloseProject() override;
	void OnExit() override;

	Console& GetConsole();

private:
	friend class ConsoleWindowTest;
	ConsoleWindowEvents* events = nullptr;
	PromptWindow promptWindow;
	DisplayWindow displayWindow;
	Console console;
};

