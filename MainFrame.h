#pragma once
#include <Wex/CustomWindow.h>
#include <memory>
#include "DocumentView.h"
#include "Document.h"

class MainFrame : public Wex::CustomWindow<MainFrame>
{
public:
	MainFrame() = default;
	MainFrame(const MainFrame& rhs) = delete;
	~MainFrame() = default;

	MainFrame& operator=(const MainFrame& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnSize(int type, const Wex::Size& size) override;
	void OnDestroy() override;

private:
	friend class MainFrameTest;
	DocumentView documentView;
	std::shared_ptr<Document> document;
};

