#include <Wex/WindowsInclude.h>
#include "Application.h"
#include "CommandLine.h"
#include "MainFrame.h"
#include <Wex/ProcessInstance.h>
#include "resource.h"

int Application::Run(const CommandLine& arguments, int showWindow)
{
	MainFrame mainFrame;
	mainFrame.Create(nullptr, "C++ IDE V2", WS_OVERLAPPEDWINDOW);
	mainFrame.Show(showWindow);

	auto accelerators = ::LoadAccelerators(
		Wex::ProcessInstance::Get(),
		MAKEINTRESOURCE(IDA_MAINFRAME));
	for (MSG msg; ; )
	{
		switch (::GetMessage(&msg, 0, 0, 0))
		{
		case -1:
			continue;
		case 0:
			return msg.wParam;
		}
		if (::TranslateAccelerator(mainFrame, accelerators, &msg))
			continue;
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return 0;
}

