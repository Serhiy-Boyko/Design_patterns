#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

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
	Document *pdoc;
	bool status;
public:
	Command(Document *p) : pdoc(p) {}
	virtual void execute() = 0;
	void enabled() { status = 1; }
	void disabled() { status = 0; }
	bool getstatus() { return status; }
};
//-----------------------------------------------------------------
// клас обробки натискання кнопки "Створити"
class ButtonCreate : public Command {
public:
	ButtonCreate(Document *p) : Command(p) {}
	/*virtual*/ void execute() { if (status) pdoc->Create(); }
};

// клас обробки вибору контекстного меню "Створити"
class CMenuCreate : public Command {
public:
	CMenuCreate(Document *p) : Command(p) {}
	/*virtual*/ void execute() { if (status) pdoc->Create(); }
};
//-----------------------------------------------------------------
// клас обробки натискання кнопки "Друкувати"
class ButtonPrint : public Command {
public:
	ButtonPrint(Document *p) : Command(p) {}
	/*virtual*/ void execute() { if (status) pdoc->Print(); }
};

// клас обробки вибору контекстного меню "Друкувати"
class CMenuPrint : public Command {
public:
	CMenuPrint(Document *p) : Command(p) {}
	/*virtual*/ void execute() { if (status) pdoc->Print(); }
};
//-----------------------------------------------------------------
// клас обробки натискання кнопки "Відкрити"
class ButtonOpen : public Command {
public:
	ButtonOpen(Document *p) : Command(p) {}
	/*virtual*/ void execute() {
		if (status) pdoc->Open(EnterFn("opening"));
	}
};

// клас обробки вибору контекстного меню "Відкрити"
class CMenuOpen : public Command {
public:
	CMenuOpen(Document *p) : Command(p) {}
	/*virtual*/ void execute() {
		if (status) pdoc->Open(EnterFn("opening"));
	}
};
//-----------------------------------------------------------------
// клас обробки натискання кнопки "Зберегти"
class ButtonSave : public Command {
public:
	ButtonSave(Document *p) : Command(p) {}
	/*virtual*/ void execute() {
		if (status) pdoc->Save(EnterFn("saving"));
	}
};

// клас обробки вибору контекстного меню "Зберегти"
class CMenuSave : public Command {
public:
	CMenuSave(Document *p) : Command(p) {}
	/*virtual*/ void execute() {
		if (status) pdoc->Save(EnterFn("saving"));
	}
};
//-----------------------------------------------------------------
/* клас обробки натискання кнопки "Відміна"
відновлюємо Document з тимчасового файлу "~TEMP_FILE.txt" */
class ButtonUndo : public Command {
public:
	ButtonUndo(Document *p) : Command(p) {}
	/*virtual*/ void execute() { if (status) pdoc->Undo(); }
};

// клас обробки вибору контекстного меню "Відміна"
class CMenuUndo : public Command {
public:
	CMenuUndo(Document *p) : Command(p) {}
	/*virtual*/ void execute() {
		if (status) pdoc->Undo();
	}
};

//================================================================
class Mediator {
	Document *doc;
	std::vector<Command*> v;
public:
	Mediator() {
		doc = new Document;
		// створення кнопок і пунктів меню
		v.push_back(new ButtonCreate(doc));
		v.push_back(new CMenuCreate(doc));

		v.push_back(new ButtonPrint(doc));
		v.push_back(new CMenuPrint(doc));

		v.push_back(new ButtonOpen(doc)); // 4
		v.push_back(new CMenuOpen(doc));

		v.push_back(new ButtonSave(doc)); // 6
		v.push_back(new CMenuSave(doc));

		v.push_back(new ButtonUndo(doc)); // 8
		v.push_back(new CMenuUndo(doc));

		v[0]->enabled();
		v[1]->enabled();
		v[2]->disabled();
		v[3]->disabled();
		v[4]->enabled();
		v[5]->enabled();
		for (size_t i = 6; i < v.size(); i++)
			v[i]->disabled();
		ShowConsoleMenu();
	}

	void ShowConsoleMenu() {
		// bool exit = false;
		int key;
		do {
			system("cls");
			std::cout << "\nChoose of the action: " << std::endl;
			std::cout << " Escape - Exit the program " << std::endl;			
			if (v[0]->getstatus()) {
				std::cout << " F1 - ButtonCreate " << std::endl;
				std::cout << " F2 - CMenuCreate " << std::endl;
			}
			if (v[2]->getstatus()) {
				std::cout << " F3 - ButtonPrint " << std::endl;
				std::cout << " F4 - CMenuPrint " << std::endl;
			}
			if (v[4]->getstatus()) {
				std::cout << " F5 - ButtonOpen " << std::endl;
				std::cout << " F6 - CMenuOpen " << std::endl;
			}
			if (v[6]->getstatus()) {
				std::cout << " F7 - ButtonSave " << std::endl;
				std::cout << " F8 - CMenuSave " << std::endl;
			}
			if (v[8]->getstatus()) {
				std::cout << " F9 - ButtonUndo " << std::endl;
				std::cout << " F10- CMenuUndo " << std::endl;
			}

			key = _getch();
			if (key == 0) {  // якщо це функціональна клавіша
				key = _getch(); // це вже код самої клавіші
				key -= 59;
			}
			if (key < v.size()) // якщо це клавіша з функціоналом
				if (v[key]->getstatus())
					v[key]->execute();
				
			switch (key) {
			case 0: // створити документ
			case 1: DocPrepared(); break;
			case 2: // друк
			case 3: system("pause"); break;
			case 4: // відкрити документ
			case 5: doc->Print();
				enabledAll(); system("pause"); break;
			case 6: // зберегти документ
			case 7: system("pause"); break;
			case 8: // відміна
			case 9: DocPrepared(); system("pause"); break;
			}
			// 
		} while (key != 27);
	}

	void DocPrepared() {
		for (size_t i = 0; i < v.size() - 2; i++)
			v[i]->enabled();
	}

	void enabledAll() {
		for (size_t i = 0; i < v.size(); i++)
			v[i]->enabled();
	}

	~Mediator() {
		for (size_t i = 0; i < v.size(); i++)
			delete v[i];
	}
};

int main()
{
	Mediator A;
	// A.ShowConsoleMenu();
	std::cout << " End of the program... " << std::endl;
	system("Pause");
	return 0;
}