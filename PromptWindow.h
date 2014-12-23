#pragma once
#include <Wex/CustomWindow.h>
#include "PromptWindowEvents.h"
#include <Wex/Font.h>
#include <Wex/Size.h>
#include <string>

class PromptWindow : public Wex::CustomWindow<PromptWindow>
{
public:
	PromptWindow(PromptWindowEvents& events);
	PromptWindow(const PromptWindow& rhs) = delete;
	~PromptWindow() = default;

	PromptWindow& operator=(const PromptWindow& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnPaint() override;
	void OnChar(int c, int count, unsigned long flags) override;
	void OnSetFocus(HWND hwnd) override;
	void OnKillFocus(HWND hwnd) override;

	void SetPrompt(const std::string& value);

private:
	friend class PromptWindowTest;
	Wex::Font font;
	Wex::Size textSize;
	PromptWindowEvents* events = nullptr;
	std::string prompt;
	std::string command;
};

