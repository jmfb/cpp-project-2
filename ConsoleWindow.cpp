#include <Wex/WindowsInclude.h>
#include "ConsoleWindow.h"

ConsoleWindow::ConsoleWindow()
	: promptWindow{ *this }
{
}

void ConsoleWindow::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "ConsoleWindow";
}

bool ConsoleWindow::OnCreate(CREATESTRUCT* cs)
{
	promptWindow.Create(GetHandle(), "", ChildWindowStyle);
	promptWindow.SetFocus();
	displayWindow.Create(GetHandle(), "", ChildWindowStyle);
	promptWindow.SetPrompt(console.GetCurrentDirectory() + "> ");
	displayWindow.SetLines(console.GetPrompt());
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
	promptWindow.SetPrompt(console.GetCurrentDirectory() + "> ");
	displayWindow.SetLines(console.GetPrompt());
}

