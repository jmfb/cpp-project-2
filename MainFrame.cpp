#include <Wex/WindowsInclude.h>
#include "MainFrame.h"

void MainFrame::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "MainFrame";
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
}

bool MainFrame::OnCreate(CREATESTRUCT* cs)
{
	document = std::make_shared<Document>();
	document->Open(R"(c:\save\code\cpp-project2\MainFrame.cpp)");

	documentView.Create(
		GetHandle(),
		"",
		WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
		0,
		GetClient());
	documentView.SetDocument(document);

	return true;
}

void MainFrame::OnSize(int type, const Wex::Size& size)
{
	documentView.Move(GetClient());
}

void MainFrame::OnDestroy()
{
	::PostQuitMessage(0);
}

