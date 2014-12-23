#pragma once
#include <string>

class SuperBoxInputEvents
{
public:
	virtual void OnOpenSelection() = 0;
	virtual void OnSelectPrevious() = 0;
	virtual void OnSelectNext() = 0;
	virtual void OnUpdateFilter(const std::string& filter) = 0;
	virtual void OnCancelSearch() = 0;
};

