#include <iostream>
#include <memory>

// https://www.badprog.com/c-design-pattern-proxy

class IPage {
public:
	virtual ~IPage() {};
	virtual void displayText() = 0;
	virtual void displayImage() = 0;
	virtual void displayVideo() = 0;
	virtual void displayEmpty() = 0;
};

class Page : public IPage {
public:
	Page();
	~Page();
	void displayText() override;
	void displayImage() override;
	void displayVideo() override;
	void displayEmpty() override;
};

Page::Page() {
	std::cout << __FUNCTION__ << std::endl;
}

Page::~Page() {
	std::cout << std::endl << __FUNCTION__ << std::endl;
}

void Page::displayText() {
	std::cout << "Displaying text." << std::endl;
}

void Page::displayImage() {
	std::cout << "Displaying an image." << std::endl;
}

void Page::displayVideo() {
	std::cout << "Displaying a video." << std::endl;
}

void Page::displayEmpty() {
	std::cout << "Sorry nothing to display." << std::endl;
}

class PageProxy : public IPage {
public:
	PageProxy();
	~PageProxy();
	void displayText() override;
	void displayImage() override;
	void displayVideo() override;
	void displayEmpty() override;

	void setCurrentPage(int currentPage);
	const int getCurrentPage() const;
	std::shared_ptr<Page> getPage();
	void displayContent(int pageNumber);
private:
	int _currentPage;
	std::shared_ptr<Page> _page;
};

PageProxy::PageProxy() {
	std::cout << __FUNCTION__ << std::endl;
	_page = NULL;
}

PageProxy::~PageProxy() {
	std::cout << __FUNCTION__ << std::endl;
}

std::shared_ptr<Page> PageProxy::getPage() {
	if (NULL == _page)
		_page = std::make_shared<Page>();
	return _page;
}

void PageProxy::setCurrentPage(int currentPage) {
	_currentPage = currentPage;
}

const int PageProxy::getCurrentPage() const {
	return _currentPage;
}

void PageProxy::displayContent(int pageNumber) {
	setCurrentPage(pageNumber);
	std::cout << "On page \"" << getCurrentPage();
	std::cout << "\":" << std::endl;
	switch (pageNumber)
	{
	case 1:
		getPage()->displayText();
		break;
	case 24:
		getPage()->displayText();
		getPage()->displayImage();
		break;
	case 37:
		getPage()->displayText();
		getPage()->displayImage();
		getPage()->displayVideo();
		break;
	default:
		getPage()->displayEmpty();
		break;
	}
	std::cout << std::endl;
}

void PageProxy::displayText() {}
void PageProxy::displayImage() {}
void PageProxy::displayVideo() {}
void PageProxy::displayEmpty() {}

class Document {
public:
	Document();
	~Document();

	void open(int page = 1);
	void initProxy();
	void changeToPage(int pageNumber);
private:
	PageProxy _proxy;
};

Document::Document() {
	std::cout << __FUNCTION__ << std::endl;
	initProxy();
}

Document::~Document() {
	std::cout << __FUNCTION__ << std::endl;
}

void Document::open(int pageNumber) {
	_proxy.displayContent(pageNumber);
}

void Document::initProxy() {}

void Document::changeToPage(int pageNumber) {
	_proxy.displayContent(pageNumber);
}

int main() {
	Document doc;
	doc.open(); // by default it opens page 1
	doc.changeToPage(4);
	doc.changeToPage(15);
	doc.changeToPage(24);
	doc.changeToPage(1);
	doc.changeToPage(37);
	doc.changeToPage(59);
	system("Pause");
	return 0;
}