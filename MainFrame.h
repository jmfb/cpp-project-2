#pragma once
#include <Wex/CustomWindow.h>
#include <memory>
#include "DocumentWindow.h"
#include "Document.h"
#include "ConsoleWindow.h"
#include "Project.h"
#include "SuperBox.h"

class MainFrame :
	public Wex::CustomWindow<MainFrame>,
	public ConsoleWindowEvents,
	public SuperBoxEvents
{
public:
	MainFrame();
	MainFrame(const MainFrame& rhs) = delete;
	~MainFrame() = default;

	MainFrame& operator=(const MainFrame& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	void OnActivate(short state, bool minimized, HWND hwnd) override;
	void OnCommand(WORD id, WORD code, HWND from) override;
	bool OnCreate(CREATESTRUCT* cs) override;
	void OnSize(int type, const Wex::Size& size) override;
	void OnDestroy() override;

	void OnNewProject(
		const std::string& directory,
		const std::string& name) override;
	void OnOpenProject(const std::string& fullPath) override;
	void OnCloseProject() override;
	void OnExit() override;

	void OnOpenSelection(const std::string& value) override;
	void OnCancelSearch() override;

	void OnSuperBox();
	void OnCloseDocument();

private:
	void SwitchActiveWindow(Wex::Window window);

private:
	friend class MainFrameTest;
	DocumentWindow documentWindow;
	ConsoleWindow consoleWindow;
	Wex::Window activeWindow;
	Project project;
	std::shared_ptr<Document> document;
	SuperBox superBox;
};

