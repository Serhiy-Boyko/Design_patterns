#include <iostream>
#include <string>

/* Завдання - вивести оформлений текст:

<<<---_TEXT_--->>>

*/

// 1. " Наименьший общий знаменатель"
class Widget {
public:
	virtual std::string get() = 0;
};

// 3. Основной класс, использующий отношение "является"
class Text : public Widget {
	std::string text;
public:
	Text(std::string t) : text(t) {}
	virtual std::string get() { return text; }
};

// 2. Базовый класс второго уровня
class Underlines : public Widget {  // 3. использует отношение "является"
	Widget *wid; // 4. отношение "имеет"
public:
	Underlines(Widget *w) : wid(w) {}
	virtual	std::string get() { return "_" + wid->get() + "_"; } // 5. делегирование
};

// 6. Дополнительное декорирование
class Dahes : public Widget {
	Widget *wid;
public:
	Dahes(Widget *w) : wid(w) {}
	virtual	std::string get() { return "---" + wid->get() + "---"; } // 5. делегирование
};

// 6. Дополнительное декорирование
class LessMore : public Widget {
	Widget *wid;
public:
	LessMore(Widget *w) : wid(w) {}
	virtual	std::string get() { return "<<<" + wid->get() + ">>>"; } // 5. делегирование
};

int main()
{
	// 8. Клиент ответственен за конфигурирование нужной функциональности
	Widget *aWidget = new LessMore(
		new Dahes(
			new Underlines(
				new Text("TEXT"))));
	std::cout << aWidget->get() << std::endl;

	Widget *bWidget = new Underlines(
		new Dahes(
			new LessMore(
				new Text("TEXT"))));
	std::cout << bWidget->get() << std::endl;
	system("Pause");
	return 0;
}

