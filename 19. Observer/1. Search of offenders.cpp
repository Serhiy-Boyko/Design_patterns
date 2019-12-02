/* Task 1. Реалізувати пошук злочинців на "Дикому Заході".
Суддя видає ордери на арешт злочинців і розсилає їх шерифу, мисливцю за головами і маршалу. Шериф додає злочинця до списку розшукуваних, окрім «Біла чотири пальці», якого «кришує».  Мисливець і маршал можуть мати лише одну ціль пошуку, при чому маршал береться за будь-якого злочинця, якщо не зайнятий, а мисливець лише за тих, за кого дають понад 1000 доларів, при умові, що він вже не зайнятий іншим пошуком. */
#include <iostream>
#include <string>
#include <vector>

class Offender { // правопорушник
	std::string name;
	int dangerous; // рівень небезпеки
	int reward;    // винагорода
public:
	Offender(std::string n, int d, int r) 
		: name(n), dangerous(d), reward(r) {}

	void Print() {
		std::cout << " Wanted: " << name;
		std::cout << " Dangerous: " << dangerous;
		std::cout << " Reward: " << reward << std::endl;
	}

	std::string getname() { return name; }
	int getdangerous() { return dangerous; };
	int getreward() { return reward; };
};

class Observer {
public:
	virtual void update(Offender *off) = 0;
};

/* Суддя (Subject), він оголошує злочинців в розшук
і надсилає повідомлення потенційним пошукачам */
class Judge {
	std::vector<Offender*> Offenders; // список правопорушників
	std::vector<Observer*> Views;     // список спостерігачів
public:
	void addObserver(Observer *obs) { Views.push_back(obs); }

	void addOffender(Offender *off) {
		Offenders.push_back(off);
		std::cout << "------------------------" << std::endl;
		std::cout << "Prosecutor:";
		off->Print();
		notify(off);
	}

	void notify(Offender *off) {
		for (int i = 0; i < Views.size(); ++i)
			Views[i]->update(off);
	}
};

class Sheriff : public Observer {
	std::vector<Offender*> targets;
public:
	Sheriff(Judge *model) { model->addObserver(this); }

	/* virtual */ void update(Offender *off) {
		if (off->getname() != "Bill four fingers") {// шериф його "кришує"
			targets.push_back(off);
			std::cout << " Sheriff: Understood! " << std::endl;
		}
	}
};

class Hunter : public Observer {
	Offender *target;
public:
	Hunter(Judge *model) : target(nullptr) { model->addObserver(this); }

	/* virtual */ void update(Offender *off) {
		if (off->getreward() > 1000 && !target) {
			target = off;
			std::cout << " Hunter: I take him! " << std::endl;
		}
		else
			std::cout << " Hunter: Not interesting! " << std::endl;
	}
};

class Marshal : public Observer {
	Offender *target;
public:
	Marshal(Judge *model) : target(nullptr) { model->addObserver(this); }

	/* virtual */ void update(Offender *off) {
		if (!target) {
			target = off;
			std::cout << " Marshal: Order is accepted! " << std::endl;
		}
	}
};

int main() {
	Judge judge;
	Sheriff s(&judge);
	Hunter h(&judge);
	Marshal m(&judge);

	judge.addOffender(new Offender("Dirty Harry", 4, 700));
	judge.addOffender(new Offender("Bill four fingers", 7, 2100));
	judge.addOffender(new Offender("Mad Bart", 9, 3800));
	system("pause");
	return 0;
}
