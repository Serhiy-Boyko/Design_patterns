#include <iostream>
#include <string>
using namespace std;

// Иерархия классов, определяющая алгоритмы сжатия файлов
class Compression {
public:
	virtual void compress(string f) = 0;
};

class ZIP_Compression : public Compression {
public:
	void compress(string f) { cout << f << " ZIP-compression" << endl; }
};

class ARJ_Compression : public Compression {
public:
	void compress(string f) { cout << f << " ARJ-compression" << endl; }
};

class RAR_Compression : public Compression {
public:
	void compress(string f) { cout << f << " RAR-compression" << endl;	}
};

// Класс для использования
class Compressor {
	Compression* p;
public:
	Compressor(Compression* comp) : p(comp) {}
	~Compressor() { delete p; }
	void ChangeCompression(Compression* comp) { p = comp; }
	void compress(const string f) { p->compress(f); }
};

void main() {
	Compression *zip = new ZIP_Compression;
	Compression *rar = new RAR_Compression;
	Compression *arj = new ARJ_Compression;

	Compressor *p = new Compressor(zip);
	p->compress("file.txt");
	p->ChangeCompression(rar);
	p->compress("file.txt");
	delete p;
}