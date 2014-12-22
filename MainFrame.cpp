#include <Wex/WindowsInclude.h>
#include "MainFrame.h"

MainFrame::MainFrame()
	: consoleWindow{ *this }
{
}

void MainFrame::OnActivate(short state, bool minimized, HWND hwnd)
{
	consoleWindow.SetFocus();
}

void MainFrame::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "MainFrame";
}

bool MainFrame::OnCreate(CREATESTRUCT* cs)
{
	consoleWindow.Create(GetHandle(), "", ChildWindowStyle);
	return true;
}

void MainFrame::OnSize(int type, const Wex::Size& size)
{
	consoleWindow.Move(GetClient());
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

