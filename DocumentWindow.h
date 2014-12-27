#pragma once
#include <Wex/CustomWindow.h>
#include <Wex/Font.h>
#include <Wex/Size.h>
#include <memory>
#include "DocumentView.h"

class DocumentWindow : public Wex::CustomWindow<DocumentWindow>
{
public:
	DocumentWindow();
	DocumentWindow(const DocumentWindow& rhs) = delete;
	~DocumentWindow() = default;

	DocumentWindow& operator=(const DocumentWindow& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnPaint() override;
	void OnSize(int type, const Wex::Size& size) override;

	void OnPageDown();
	void OnPageUp();
	
	void SetDocument(std::shared_ptr<Document> value);

private:
	friend class DocumentWindowTest;
	Wex::Font font;
	Wex::Size textSize;
	DocumentView documentView;
};

