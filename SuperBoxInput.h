#pragma once
#include <Wex/CustomWindow.h>
#include <Wex/Font.h>
#include <Wex/Size.h>
#include <string>
#include "SuperBoxInputEvents.h"

class SuperBoxInput : public Wex::CustomWindow<SuperBoxInput>
{
public:
	SuperBoxInput(SuperBoxInputEvents& events);
	SuperBoxInput(const SuperBoxInput& rhs) = delete;
	~SuperBoxInput() = default;

	SuperBoxInput& operator=(const SuperBoxInput& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnPaint() override;
	void OnChar(int c, int count, unsigned long flags) override;
	void OnKeyDown(int c, int count, unsigned long flags) override;
	void OnSetFocus(HWND hwnd) override;
	void OnKillFocus(HWND hwnd) override;

private:
	friend class SuperBoxInputTest;
	SuperBoxInputEvents* events = nullptr;
	Wex::Font font;
	Wex::Size textSize;
	std::string value;
};

