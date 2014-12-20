#pragma once
#include <Wex/CustomWindow.h>
#include <Wex/PaintDeviceContext.h>
#include <Wex/ClientDeviceContext.h>
#include <Wex/MemoryDeviceContext.h>
#include <functional>
#include <string>
#include <vector>
#include <typeinfo>

template <typename Value>
class TabStrip : public Wex::CustomWindow<TabStrip<Value>>
{
public:
	TabStrip(std::function<std::string(const Value&)> getDisplayText)
		: getDisplayText(getDisplayText)
	{
	}
	TabStrip(const TabStrip<Value>& rhs) = delete;
	~TabStrip() = default;

	TabStrip<Value>& operator=(const TabStrip<Value>& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass)
	{
		static const std::string className{ "TabStrip<" + std::string{ typeid(Value).name() } + ">" };
		windowClass.lpszClassName = className.c_str();
		windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
		windowClass.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
	}

	static const auto backgroundColor = RGB(0, 0, 0);
	static const auto hoverColor = RGB(0, 255, 0);
	static const auto selectedColor = RGB(0, 0, 255);
	static const auto textColor = RGB(255, 255, 255);

	void OnPaint() override
	{
		Wex::PaintDeviceContext paintDeviceContext{ this->GetHandle() };
		Wex::MemoryDeviceContext deviceContext{ paintDeviceContext };
		deviceContext.FillSolidRect(this->GetClient(), backgroundColor);
		for (auto index = 0; index < GetItemCount(); ++index)
			DrawItem(deviceContext, index);
	}

	void OnMouseMove(const Wex::Point& pt, unsigned long flags) override
	{
		if (!trackingMouse)
		{
			trackingMouse = true;
			this->TrackMouse(TME_LEAVE);
		}
		Wex::ClientDeviceContext deviceContext{ this->GetHandle() };
		auto index = HitTest(deviceContext, pt);
		if (index == hoverIndex)
			return;
		hoverIndex = index;
		this->Invalidate(false);
	}

	void OnMouseLeave() override
	{
		trackingMouse = false;
		hoverIndex = -1;
		this->Invalidate(false);
	}

	void OnLButtonDown(const Wex::Point& pt, unsigned long flags)
	{
		Wex::ClientDeviceContext deviceContext{ this->GetHandle() };
		auto index = HitTest(deviceContext, pt);
		if (index == -1 || index == selectedIndex)
			return;
		selectedIndex = index;
		this->Invalidate(false);
	}

	int AddItem(Value value)
	{
		values.push_back(value);
		return values.size() - 1;
	}
	int InsertItem(int insertBefore, Value value)
	{
		values.insert(values.begin() + insertBefore, value);
		return insertBefore;
	}
	void RemoveItem(int index)
	{
		values.erase(values.begin() + index);
	}
	void RemoveAllItems()
	{
		values.clear();
	}
	int GetItemCount() const
	{
		return values.size();
	}
	const Value& GetItem(int index) const
	{
		return values[index];
	}
	void SelectItem(int index)
	{
		selectedIndex = index;
	}
	int GetSelectedIndex() const
	{
		return selectedIndex;
	}

private:
	int HitTest(Wex::DeviceContext& deviceContext, const Wex::Point& pt) const
	{
		for (auto index = 0; index < GetItemCount(); ++index)
			if (GetItemRect(deviceContext, index).Contains(pt))
				return index;
		return -1;
	}

	void DrawItem(Wex::DeviceContext& deviceContext, int index) const
	{
		auto rect = GetItemRect(deviceContext, index);
		auto backColor = GetBackgroundColor(index);
		deviceContext.FillSolidRect(rect, backColor);
		deviceContext.SetBackColor(backColor);
		deviceContext.SetTextColor(textColor);
		deviceContext.DrawText(getDisplayText(values[index]), rect);
	}

	COLORREF GetBackgroundColor(int index) const
	{
		if (index == selectedIndex)
			return selectedColor;
		if (index == hoverIndex)
			return hoverColor;
		return backgroundColor;
	}

	Wex::Rect GetItemRect(Wex::DeviceContext& deviceContext, int index) const
	{
		const auto itemSpacing = 5;
		auto left = 0;
		for (auto indexBefore = 0; indexBefore < index; ++indexBefore)
			left += GetItemWidth(deviceContext, indexBefore) + itemSpacing;
		return
		{
			Wex::Point{ left, 0 },
			Wex::Size{ GetItemWidth(deviceContext, index), this->GetClient().GetHeight() }
		};
	}

	int GetItemWidth(Wex::DeviceContext& deviceContext, int index) const
	{
		const auto selectedItemOptionsWidth = 20;
		auto displayTextWidth = deviceContext
			.MeasureString(getDisplayText(values[index]), this->GetClient())
			.GetWidth();
		if (index != selectedIndex)
			return displayTextWidth;
		return displayTextWidth + selectedItemOptionsWidth;
	}

private:
	friend class TabStripTest;
	std::function<std::string(const Value&)> getDisplayText;
	std::vector<Value> values;
	int selectedIndex = -1;
	int hoverIndex = -1;
	bool trackingMouse = false;
};

