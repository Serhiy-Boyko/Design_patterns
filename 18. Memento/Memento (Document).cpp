#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <time.h>
#include <cassert>
#include <Windows.h>

// Memento
class Memento {
	size_t count_of_symbols;
	size_t count_of_image;
	size_t count_of_video;
	tm *ts;
public:
	Memento(size_t s, size_t i, size_t v, tm *t) 
		: count_of_symbols(s), count_of_image(i), count_of_video(v)
	{
		ts = new tm;
		ts->tm_year = t->tm_year + 1900;
		ts->tm_mon = t->tm_mon+1;
		ts->tm_mday = t->tm_mday;
		ts->tm_hour = t->tm_hour;
		ts->tm_min = t->tm_min;
		ts->tm_sec = t->tm_sec;
	}

	Memento(const Memento &M) {
		count_of_symbols = M.count_of_symbols;
		count_of_image = M.count_of_image;
		count_of_video = M.count_of_video;
		ts = new tm;
		ts->tm_year = M.ts->tm_year;
		ts->tm_mon = M.ts->tm_mon;
		ts->tm_mday = M.ts->tm_mday;
		ts->tm_hour = M.ts->tm_hour;
		ts->tm_min = M.ts->tm_min;
		ts->tm_sec = M.ts->tm_sec;
	}

	size_t getSymbols() { return count_of_symbols; }
	size_t getImages() { return count_of_image; }
	size_t getVideo() {	return count_of_video; }

	void Print() {
		std::cout << " " << ts->tm_mday;
		std::cout << "-" << ts->tm_mon;
		std::cout << "-" << ts->tm_year;
		std::cout << " " << ts->tm_hour;
		std::cout << ":" << ts->tm_min;
		std::cout << ":" << ts->tm_sec;
		std::cout << " Symbols: " << count_of_symbols;
		std::cout << " Images: " << count_of_image;
		std::cout << " Video: " << count_of_video << std::endl;
	}

	~Memento() { delete ts; }
};

// Originator
class Document {
	size_t count_of_symbols;
	size_t count_of_image;
	size_t count_of_video;
public:
	Document() : count_of_symbols(0), count_of_image(0), count_of_video(0) {
		std::cout << "Create new document... " << std::endl;
	}

	void Print() {
		std::cout << "Printing of current document... " << std::endl;
		std::cout << "   Symbols: " << count_of_symbols << std::endl;
		std::cout << "    Images: " << count_of_image << std::endl;
		std::cout << "     Video: " << count_of_video << std::endl;
	}

	void AddText(size_t cnt) {
		std::cout << "  Add symbols: " << cnt << std::endl;
		count_of_symbols += cnt;
	}

	void AddImage() {
		std::cout << "  Add image " << std::endl;
		count_of_image++;
	}

	void AddVideo() {
		std::cout << "  Add video " << std::endl;
		count_of_video++;
	}

	// збереження стану
	Memento SaveDocument() {
		std::cout << "Save document... " << std::endl;
		time_t t = time(NULL);
		tm *ts = localtime(&t);
		return Memento({ count_of_symbols, count_of_image, 
			count_of_video, ts });
	}

	// відновлення стану
	void RestoreDocument(Memento memento) {
		std::cout << "Restore document... " << std::endl;
		count_of_symbols = memento.getSymbols();
		count_of_image = memento.getImages();
		count_of_video = memento.getVideo();
	}

	~Document() {}
};

// Caretaker
class DocHistory {
	std::vector<Memento> History;
public:
	void push(Memento m) { History.push_back(m); }

	Memento ReturnDoc(size_t i) {
		if (i < History.size())
			return History[i];
		else
			assert(false);
	}

	void Print() {
		std::cout << "------------------- History ------------------\n";
		for (auto m : History)
			m.Print();
		std::cout << "----------------------------------------------\n";
	};

	~DocHistory() {}
};

int main()
{
	Document doc;
	DocHistory dochistory;

	doc.AddText(100);
	doc.AddImage();
	doc.AddImage();
	doc.Print();
	dochistory.push(doc.SaveDocument());
	Sleep(1000);

	doc.AddText(200);
	doc.AddImage();
	doc.AddImage();
	doc.AddVideo();
	doc.Print();
	dochistory.push(doc.SaveDocument());
	Sleep(1000);

	doc.AddText(300);
	doc.AddVideo();
	doc.Print();
	dochistory.push(doc.SaveDocument());

	dochistory.Print();

	doc.RestoreDocument(dochistory.ReturnDoc(0));
	doc.Print();
	// doc.RestoreDocument(dochistory.ReturnDoc(7));
	system("Pause");
	return 0;
}