#pragma once
#include <Wex/CustomWindow.h>
#include "SuperBoxInput.h"
#include "SuperBoxResults.h"
#include "SuperBoxEvents.h"
#include <vector>
#include <string>

class SuperBox :
	public Wex::CustomWindow<SuperBox>,
	public SuperBoxInputEvents
{
public:
	SuperBox(SuperBoxEvents& events);
	SuperBox(const SuperBox& rhs) = delete;
	~SuperBox() = default;

	SuperBox& operator=(const SuperBox& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnSetFocus(HWND hwnd) override;
	void OnSize(int type, const Wex::Size& size) override;
	void OnPaint() override;

	void OnOpenSelection() override;
	void OnSelectPrevious() override;
	void OnSelectNext() override;
	void OnUpdateFilter(const std::string& filter) override;
	void OnCancelSearch() override;

private:
	friend class SuperBoxTest;
	SuperBoxEvents* events = nullptr;
	SuperBoxInput input;
	SuperBoxResults results;
	std::vector<std::string> possibleResults;
};

