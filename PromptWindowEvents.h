#pragma once
#include <string>

class PromptWindowEvents
{
public:
	virtual void OnExecuteCommand(const std::string& value) = 0;
};

