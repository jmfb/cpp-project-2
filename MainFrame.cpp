#include <Wex/WindowsInclude.h>
#include "MainFrame.h"
#include "resource.h"
#include <Wex/Path.h>
#include <Wex/String.h>
#include <Wex/Icon.h>
#include <algorithm>

MainFrame::MainFrame()
	: consoleWindow{ *this }, superBox{ *this, project }
{
	HandleCommand(ID_SUPERBOX, &MainFrame::OnSuperBox);
	HandleCommand(ID_CLOSE_DOCUMENT, &MainFrame::OnCloseDocument);
}

void MainFrame::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "MainFrame";
	windowClass.hIcon = Wex::Icon::LoadLarge(IDI_MAINFRAME);
	windowClass.hIconSm = Wex::Icon::LoadSmall(IDI_MAINFRAME);
}

void MainFrame::OnActivate(short state, bool minimized, HWND hwnd)
{
	if (superBox.IsValid())
		superBox.SetFocus();
	else
		activeWindow.SetFocus();
}

void MainFrame::OnCommand(WORD id, WORD code, HWND from)
{
	if (id >= ID_FIRST_EDITOR_COMMAND &&
		id <= ID_LAST_EDITOR_COMMAND &&
		activeWindow == documentWindow &&
		documentWindow.IsValid())
		documentWindow.OnCommand(id, code, from);
	else
		Wex::CustomWindow<MainFrame>::OnCommand(id, code, from);
}

bool MainFrame::OnCreate(CREATESTRUCT* cs)
{
	consoleWindow.Create(GetHandle(), "", ChildWindowStyle);
	documentWindow.Create(GetHandle(), "", ChildWindowStyle);
	documentWindow.Hide();
	activeWindow = consoleWindow;
	consoleWindow.SetFocus();
	return true;
}

void MainFrame::OnSize(int type, const Wex::Size& size)
{
	activeWindow.Move(GetClient());
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
	project.Close();
	documentViews.clear();
	consoleWindow.GetConsole().SwitchMode(Console::Initial);
}

void MainFrame::OnExit()
{
	Close();
}

void MainFrame::OnOpenSelection(const std::string& value)
{
	auto fullPath = Wex::Path::Combine(project.GetProjectDirectory(), value);
	if (Wex::String::ToLower(fullPath) == Wex::String::ToLower(project.GetFileName()))
		MsgBox("Edit Project");
	else
	{
		SwitchActiveWindow(documentWindow);
		auto iter = std::find_if(
			documentViews.begin(),
			documentViews.end(),
			[&](const DocumentView& view){ return view.IsFor(fullPath); });
		if (iter == documentViews.end())
			documentViews.emplace_back(fullPath);
		else
			documentViews.splice(documentViews.end(), documentViews, iter);
		ViewDocument(&documentViews.back());
	}
	superBox.Close();
	activeWindow.SetFocus();
}

void MainFrame::OnCancelSearch()
{
	superBox.Close();
	activeWindow.SetFocus();
}

void MainFrame::OnSuperBox()
{
	if (!project.IsOpen() || superBox.IsValid())
		return;
	superBox.Create(GetHandle(), "", ChildWindowStyle);
	OnSize(0, {});
	activeWindow.SetPos(superBox, {}, SWP_NOSIZE|SWP_NOMOVE);
	superBox.SetFocus();
}

void MainFrame::OnCloseDocument()
{
	if (documentViews.empty())
		return;
	ViewDocument(nullptr);
	documentViews.pop_back();
	if (documentViews.empty())
		SwitchActiveWindow(consoleWindow);
	else
		ViewDocument(&documentViews.back());
}

void MainFrame::SwitchActiveWindow(Wex::Window window)
{
	if (activeWindow == window)
		return;
	window.Move(GetClient());
	window.Show();
	activeWindow.Hide();
	window.SetFocus();
	activeWindow = window;
}

void MainFrame::ViewDocument(DocumentView* documentView)
{
	const std::string applicationName{ "C++ IDE V2" };
	if (documentView == nullptr)
		SetText(applicationName);
	else
		SetText(applicationName + ": " + documentView->GetTitle());
	documentWindow.SetDocumentView(documentView);
}

