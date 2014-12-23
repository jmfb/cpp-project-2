#include <Wex/WindowsInclude.h>
#include "SuperBox.h"
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "ColorScheme.h"

SuperBox::SuperBox(SuperBoxEvents& events)
	: events{ &events }, input{ *this }
{
}

void SuperBox::SetupClass(WNDCLASSEX& windowClass)
{
	windowClass.lpszClassName = "SuperBox";
	windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	windowClass.style = CS_HREDRAW|CS_VREDRAW;
}

bool SuperBox::OnCreate(CREATESTRUCT* cs)
{
	//TODO: Load possibleResults
	possibleResults.clear();
	possibleResults.push_back("Hello");
	possibleResults.push_back("World");
	input.Create(GetHandle(), "", ChildWindowStyle);
	input.SetFocus();
	results.Create(GetHandle(), "", ChildWindowStyle);
	return true;
}

void SuperBox::OnSetFocus(HWND hwnd)
{
	input.SetFocus();
}

void SuperBox::OnSize(int type, const Wex::Size& size)
{
	auto client = GetClient();
	client.Inflate({ -4, -4 });
	auto inputRect = client;
	inputRect.SetHeight(17);
	input.Move(inputRect);
	auto resultsRect = client - inputRect;
	resultsRect.top += 4;
	results.Move(resultsRect);
}

void SuperBox::OnPaint()
{
	Wex::PaintDeviceContext paintDeviceContext{ GetHandle() };
	Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
	deviceContext.FillSolidRect(GetClient(), ColorScheme::Background::Popup);
}

void SuperBox::OnOpenSelection()
{
	if (results.HasSelection())
		events->OnOpenSelection(results.GetSelection());
}

void SuperBox::OnSelectPrevious()
{
	results.SelectPrevious();
}

void SuperBox::OnSelectNext()
{
	results.SelectNext();
}

void SuperBox::OnUpdateFilter(const std::string& filter)
{
	//TODO: filter results
	results.SetResults(filter, possibleResults);
}

void SuperBox::OnCancelSearch()
{
	events->OnCancelSearch();
}

