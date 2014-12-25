#include <Wex/WindowsInclude.h>
#include "SuperBox.h"
#include <Wex/PaintDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include "ColorScheme.h"

SuperBox::SuperBox(SuperBoxEvents& events, Project& project)
	: events{ &events }, project{ &project }, input{ *this }
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
	possibleResults = project->GetAllFiles();
	input.Create(GetHandle(), "", ChildWindowStyle);
	input.SetFocus();
	results.Create(GetHandle(), "", ChildWindowStyle);
	OnUpdateFilter("");
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
	std::vector<std::string> matches;
	for (const auto& possibleResult : possibleResults)
	{
		if (!PartialWordMatch(filter, possibleResult))
			continue;
		matches.push_back(possibleResult);
		if (matches.size() >= 20)
			break;
	}
	results.SetResults(filter, matches);
}

void SuperBox::OnCancelSearch()
{
	events->OnCancelSearch();
}

bool SuperBox::PartialWordMatch(const std::string& filter, const std::string& value)
{
	if (filter.empty())
		return true;

	auto iter = value.begin();
	for (auto c : filter)
	{
		for (; iter != value.end(); ++iter)
		{
			if (std::tolower(c) == std::tolower(*iter))
				break;
		}
		if (iter == value.end())
			return false;
		++iter;
	}

	return true;
}

