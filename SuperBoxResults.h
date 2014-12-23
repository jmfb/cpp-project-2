#pragma once
#include <Wex/CustomWindow.h>
#include <Wex/Font.h>
#include <Wex/Size.h>
#include <vector>
#include <string>
#include "ColoredText.h"

class SuperBoxResults : public Wex::CustomWindow<SuperBoxResults>
{
public:
	SuperBoxResults() = default;
	SuperBoxResults(const SuperBoxResults& rhs) = delete;
	~SuperBoxResults() = default;

	SuperBoxResults& operator=(const SuperBoxResults& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnPaint() override;

	void SetResults(const std::string& filter, const std::vector<std::string>& value);
	void SelectPrevious();
	void SelectNext();
	bool HasSelection() const;
	const std::string& GetSelection() const;

private:
	ColoredLine Colorize(const std::string& result, COLORREF background) const;

private:
	friend class SuperBoxResultsTest;
	Wex::Font font;
	Wex::Size textSize;
	std::string filter;
	std::vector<std::string> results;
	int selection = 0;
};

