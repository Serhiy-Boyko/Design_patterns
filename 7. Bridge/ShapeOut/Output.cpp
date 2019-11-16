#include "Output.h"

void console::outputInfo() {
	std::cout << p->getname() << " : " << std::endl;
	std::cout << p->getKoords() << std::endl;
}

void message::outputInfo() {
	std::string s = p->getname();
	std::string info = p->getKoords();
	// конвертируем ANSI-строки в Unicode-строки
	wchar_t *ptr = new wchar_t[s.length() + 1];
	mbstowcs(ptr, s.c_str(), s.length());
	ptr[s.length()] = '\0';
	wchar_t *p = new wchar_t[info.length() + 1];
	mbstowcs(p, info.c_str(), info.length());
	p[info.length()] = '\0';

	MessageBox(0, p, ptr, MB_OK | MB_ICONINFORMATION);
}

void logfile::outputInfo() {
	std::ofstream f("log.txt", std::ios::app);
	f << p->getname() << " : " << std::endl;
	f << p->getKoords() << std::endl;
	f.close();
}