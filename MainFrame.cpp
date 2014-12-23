#include <Wex/WindowsInclude.h>
#include "MainFrame.h"

MainFrame::MainFrame()
	: consoleWindow{ *this }, superBox{ *this }
{
}

void MainFrame::OnActivate(short state, bool minimized, HWND hwnd)
{
	if (superBox.IsValid())
		superBox.SetFocus();
	else
		consoleWindow.SetFocus();
}

void MainFrame::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "MainFrame";
}

bool MainFrame::OnCreate(CREATESTRUCT* cs)
{
	superBox.Create(GetHandle(), "", ChildWindowStyle);
	consoleWindow.Create(GetHandle(), "", ChildWindowStyle);
	superBox.SetFocus();
	return true;
}

void MainFrame::OnSize(int type, const Wex::Size& size)
{
	consoleWindow.Move(GetClient());
	if (superBox.IsValid())
	{
		auto rect = GetClient();
		auto center = rect.GetCenter();
		rect.left = center.x - 200;
		rect.right = center.x + 200;
		rect.top = center.y - 200;
		rect.bottom = center.y + 200;
		superBox.Move(rect);
	}
}

void MainFrame::OnDestroy()
{
	::PostQuitMessage(0);
}

void MainFrame::OnNewProject(
	const std::string& directory,
	const std::string& name)
{
	project.New(directory, name);
	project.Save();
	auto& console = consoleWindow.GetConsole();
	console.SwitchMode(Console::Project);
	console.SetCurrentProjectName(project.GetName());
}

void MainFrame::OnOpenProject(const std::string& fullPath)
{
	project.Open(fullPath);
	auto& console = consoleWindow.GetConsole();
	console.SwitchMode(Console::Project);
	console.SetCurrentProjectName(project.GetName());
}

void MainFrame::OnCloseProject()
{
	consoleWindow.GetConsole().SwitchMode(Console::Initial);
}

void MainFrame::OnExit()
{
	Close();
}

void MainFrame::OnOpenSelection(const std::string& value)
{
	MsgBox(value);
	superBox.Close();
	consoleWindow.SetFocus();
}

void MainFrame::OnCancelSearch()
{
	superBox.Close();
	consoleWindow.SetFocus();
}

