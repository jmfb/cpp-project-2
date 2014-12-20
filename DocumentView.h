#pragma once
#include <Wex/CustomWindow.h>
#include <Wex/Font.h>
#include <memory>
#include "Document.h"

class DocumentView : public Wex::CustomWindow<DocumentView>
{
public:
	DocumentView() = default;
	DocumentView(const DocumentView& rhs) = delete;
	~DocumentView() = default;

	DocumentView& operator=(const DocumentView& rhs) = delete;

	static void SetupClass(WNDCLASSEX& windowClass);

	bool OnCreate(CREATESTRUCT* cs) override;
	void OnPaint() override;

	void SetDocument(std::weak_ptr<Document> value);

private:
	friend class DocumentViewTest;
	Wex::Font font;
	std::weak_ptr<Document> weakDocument;
};

