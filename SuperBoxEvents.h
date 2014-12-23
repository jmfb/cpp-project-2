#pragma once
#include <string>

class SuperBoxEvents
{
public:
	virtual void OnOpenSelection(const std::string& value) = 0;
	virtual void OnCancelSearch() = 0;
};

