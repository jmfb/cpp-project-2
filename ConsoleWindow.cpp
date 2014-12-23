#include <Wex/WindowsInclude.h>
#include "ConsoleWindow.h"

ConsoleWindow::ConsoleWindow(ConsoleWindowEvents& events)
	: events{ &events }, promptWindow{ *this }, console{ *this }
{
}

void ConsoleWindow::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "ConsoleWindow";
}

bool ConsoleWindow::OnCreate(CREATESTRUCT* cs)
{
	promptWindow.Create(GetHandle(), "", ChildWindowStyle);
	displayWindow.Create(GetHandle(), "", ChildWindowStyle);
	promptWindow.SetPrompt(console.GetPrompt());
	displayWindow.SetLines(console.GetDisplay());
	return true;
}

void ConsoleWindow::OnSetFocus(HWND hwnd)
{
	promptWindow.SetFocus();
}

void ConsoleWindow::OnSize(int type, const Wex::Size& size)
{
	auto client = GetClient();
	auto promptRect = client;
	promptRect.SetHeight(17);
	promptWindow.Move(promptRect);
	auto displayRect = client - promptRect;
	displayWindow.Move(displayRect);
}

void ConsoleWindow::OnExecuteCommand(const std::string& command)
{
	console.ExecuteCommand(command);
	promptWindow.SetPrompt(console.GetPrompt());
	displayWindow.SetLines(console.GetDisplay());
}

void ConsoleWindow::OnNewProject(const std::string& name)
{
	events->OnNewProject(console.GetCurrentDirectory(), name);
}

void ConsoleWindow::OnOpenProject(const std::string& fullPath)
{
	events->OnOpenProject(fullPath);
}

void ConsoleWindow::OnCloseProject()
{
	events->OnCloseProject();
}

void ConsoleWindow::OnExit()
{
	events->OnExit();
}

Console& ConsoleWindow::GetConsole()
{
	return console;
}

