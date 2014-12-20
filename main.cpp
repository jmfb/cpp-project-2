#include <Wex/WindowsInclude.h>
#include <Wex/ProcessInstance.h>
#include "Application.h"
#include <exception>

int __stdcall WinMain(
	HINSTANCE instance,
	HINSTANCE,
	char*,
	int showWindow)
{
	try
	{
		Wex::ProcessInstance::Initialize(instance);
		return Application{}.Run(
			{ __argc, const_cast<const char**>(__argv) },
			showWindow);
	}
	catch (const std::exception& exception)
	{
		::MessageBox(
			nullptr,
			exception.what(),
			"Error",
			MB_OK|MB_ICONERROR);
	}
	catch (...)
	{
		::MessageBox(
			nullptr,
			"Unhandled exception.",
			"Error",
			MB_OK|MB_ICONERROR);
	}
	return 1;
}

