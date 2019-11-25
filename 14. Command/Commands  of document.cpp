#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Document {
	std::string content; // текст документа

	void Save_Temporarily() {
		if (content.length() > 0) { 
			std::ofstream f("~TEMP_FILE.txt");
			f << content;
			f.close();
		}
	}
public:
	Document() : content("") {}

	// цим ф-ям все одно, хто їх викликав (кнопка, меню чи інший спосіб)
	void Create() {
		Save_Temporarily();
		std::cout << " Create new document: " << std::endl;
		std::cout << " Enter text: " << std::endl;
		char s[200];
		gets_s(s);
		content = s;
	}

	void Print() {
		std::cout << " Printing of current document: " << '\n';
		std::cout << content << std::endl;
	}

	void Open(std::string filename) {
		Save_Temporarily();
		std::cout << " Opening of document " << filename << '\n';
		std::ifstream f(filename);
		content.clear();
		while (!f.eof())
			content += f.get();
		f.close();
	}

	void Save(std::string filename) {
		std::cout << " Saving document to file " << filename << '\n';
		std::ofstream f(filename);
		f << content;
		f.close();
	}

	void Undo() {
		std::ifstream f("~TEMP_FILE.txt");
		std::cout << " Back to the previous version ";
		if (f) {
			f >> content;
			std::cout << '\n' << content << std::endl;
		}
		else
			std::cout << "is not possible!" << std::endl;
		f.close();
	}

	~Document() { remove("~TEMP_FILE.txt"); }
};

std::string EnterFn(std::string op) {
	std::cout << " Enter filename for " << op << ": ";
	char s[200];
	gets_s(s);
	return s;
}
//================================================================
// Базовий клас
class Command {
protected:
	Command(Document *p) : pdoc(p) {}
	Document *pdoc;
public:
	virtual void execute() = 0;
};
//-----------------------------------------------------------------
// клас обробки натискання кнопки "Створити"
class ButtonCreate : public Command {
public:
	ButtonCreate(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Create(); }
};

// клас обробки вибору контекстного меню "Створити"
class CMenuCreate : public Command {
public:
	CMenuCreate(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Create(); }
};
//-----------------------------------------------------------------
// клас обробки натискання кнопки "Друкувати"
class ButtonPrint : public Command {
public:
	ButtonPrint(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Print(); }
};

// клас обробки вибору контекстного меню "Друкувати"
class CMenuPrint : public Command {
public:
	CMenuPrint(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Print(); }
};
//-----------------------------------------------------------------
// клас обробки натискання кнопки "Відкрити"
class ButtonOpen : public Command {
public:
	ButtonOpen(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Open(EnterFn("opening")); }
};

// клас обробки вибору контекстного меню "Відкрити"
class CMenuOpen : public Command {
public:
	CMenuOpen(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Open(EnterFn("opening")); }
};
//-----------------------------------------------------------------
// клас обробки натискання кнопки "Зберегти"
class ButtonSave : public Command {
public:
	ButtonSave(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Save(EnterFn("saving")); }
};

// клас обробки вибору контекстного меню "Зберегти"
class CMenuSave : public Command {
public:
	CMenuSave(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Save(EnterFn("saving")); }
};
//-----------------------------------------------------------------
/* клас обробки натискання кнопки "Відміна"
відновлюємо Document з тимчасового файлу "~TEMP_FILE.txt" */
class ButtonUndo : public Command {
public:
	ButtonUndo(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Undo(); }
};

// клас обробки вибору контекстного меню "Відміна"
class CMenuUndo : public Command {
public:
	CMenuUndo(Document *p) : Command(p) {}
	/*virtual*/ void execute() { pdoc->Undo(); }
};

int main()
{
	Document doc;
	std::vector<Command*> v;
	// створення кнопок і пунктів меню
	v.push_back(new ButtonCreate(&doc)); // 0
	v.push_back(new CMenuCreate(&doc));

	v.push_back(new ButtonPrint(&doc)); // 2
	v.push_back(new CMenuPrint(&doc));

	v.push_back(new ButtonSave(&doc)); // 4
	v.push_back(new CMenuSave(&doc));

	v.push_back(new ButtonOpen(&doc)); // 6
	v.push_back(new CMenuOpen(&doc));

	v.push_back(new ButtonUndo(&doc)); // 8
	v.push_back(new CMenuUndo(&doc));

	v[8]->execute(); // ButtonUndo
	v[0]->execute(); // ButtonCreate
	v[2]->execute(); // ButtonPrint
	v[4]->execute(); // ButtonSave

	v[6]->execute(); // ButtonOpen
	v[2]->execute(); // ButtonPrint

	v[8]->execute(); // ButtonUndo
	v[3]->execute(); // CMenuPrint

	for (size_t i = 0; i < v.size(); i++) 
		delete v[i];

	system("Pause");
	return 0;
}