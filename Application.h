#pragma once
#include "CommandLine.h"

class Application
{
public:
	Application() = default;
	Application(const Application& rhs) = delete;
	~Application() = default;

	Application& operator=(const Application& rhs) = delete;

	int Run(const CommandLine& arguments, int showWindow);

private:
	friend class ApplicationTest;
};

