#pragma once
#include <string>

class ConsoleEvents
{
public:
	virtual void OnNewProject(const std::string& name) = 0;
	virtual void OnOpenProject(const std::string& fullPath) = 0;
	virtual void OnCloseProject() = 0;
	virtual void OnExit() = 0;
};

