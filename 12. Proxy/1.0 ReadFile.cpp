#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

// ReadFile читає і виводить на екран весь файл
// ProxyReadFile читає і виводить на екран файл по одній сторінці

class IReadFile {
protected:
	virtual char *getLine() = 0;
public:
	virtual void AssignFile(std::string filename) = 0;
	virtual void PrintFile() = 0;
	virtual ~IReadFile() {};
};


class ReadFile : public IReadFile {
protected:
	std::ifstream f;
	char *str = nullptr;
	size_t fileSize;

	virtual char *getLine() override {
		f.getline(str, fileSize);
		return str;
	}
public:
	virtual void AssignFile(std::string filename) override {
		delete str;
		f.open(filename);
		f.seekg(0, SEEK_END);
		fileSize = f.tellg();
		str = new char[fileSize + 1];
		f.seekg(0);
	}

	ReadFile(std::string filename) {
		AssignFile(filename);
	}

	virtual void PrintFile() override {
		while (!f.eof())
			std::cout << getLine() << std::endl;
		f.seekg(0);
	}

	virtual ~ReadFile() {
		delete str;
		f.close();
	};

	friend class ProxyReadFile;
};

class ProxyReadFile : public IReadFile {
	ReadFile *RF = nullptr;
	std::string filename;

	virtual char *getLine() override {
		return RF->getLine();
	}
public:
	virtual void AssignFile(std::string fname) override {
		delete RF;
		filename = fname;
	}

	ProxyReadFile(std::string fname) : filename(fname) { }

	virtual void PrintFile() override {
		if (!RF)
			RF = new ReadFile(filename);
		char *s = nullptr;
		size_t cnt = 0;
		int num_of_page = 1;
		// 120 - count of char in string on screen
		const size_t nchar = 120;
		while (!RF->f.eof()) {
			s = getLine();
			
			if (cnt + strlen(s) / nchar + 1 < 29) {
				cnt += strlen(s) / nchar + 1;
				std::cout << s << std::endl;
			}
			else {
				std::cout << "------------------ Number of page: ";
				std::cout << num_of_page++ << " ------" << std::endl;
				if (_getch() == 27) { // Escape
					RF->f.seekg(0);
					std::cout << "End of printting..." << std::endl;
					break;
				}
				else {					
					cnt = strlen(s) / nchar + 1;
					std::cout << s << std::endl;
				}
			}
		}
	}

	virtual ~ProxyReadFile() { delete RF; }
};


int main() {
	//ReadFile A("Readme.txt");
	//A.PrintFile();
	ProxyReadFile B("Winamp.txt");
	B.PrintFile();

	system("Pause");
	return 0;
}