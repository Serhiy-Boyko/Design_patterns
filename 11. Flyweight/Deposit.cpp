#include <iostream>
#include <string>
#include <vector>
#include <time.h>

/* Банк пропонує клієнтам покласти кошти на депозит. Клієнт може вибрати одну з кількох пропозицій, кожна з яких містить стандартні умови. */

struct Condition
{
	std::string text; // текст стандартної угоди (умови угоди)
	bool active; // чи можна укладати нові угоди на даних умовах
	size_t count; // кількість угод на даних умовах
};

class Pool_of_conditions { 
	std::vector<Condition> conds_pool;
public:
	void AddNewCondition(std::string text_cond) {
		for (auto &i : conds_pool)
			if (i.text == text_cond)
				i.active = true;
		conds_pool.push_back({ text_cond, true, 0 });
	}

	void make_inactive_Condition(std::string text_cond) {
		for (auto i : conds_pool)
			if (i.text == text_cond)
				i.active = false;
	}

	int Find_Condition(std::string text_cond) {
		for (size_t i = 0; i < conds_pool.size(); i++)
			if (conds_pool[i].text == text_cond)
				return i;
		return -1;
	}

	int check_Condition(int index) { return conds_pool[index].active; }
	std::string getText(int index) { return conds_pool[index].text; }
	std::string operator[](int index) { return conds_pool[index].text; }
	void inc(int index) { conds_pool[index].count++; }
	void dec(int index) { conds_pool[index].count--; }

	int count_of_conditions() { return conds_pool.size(); }
};

class Deposit {
	// контекст (зовнішній стан) унікальні дані клієнтів
	std::string name;
	int suma;
	std::string date;
	int number; // conditions[number];
public:
	Deposit() : name(""), suma(0), date(""), number(0) {}
	Deposit(std::string n, int s, std::string d, int num)
		: name(n), suma(s), date(d), number(num) {}

	void Set(std::string n, int s, std::string d, int num) {
		name = n;
		suma = s;
		date = d;
		number = num;
	}

	void Print() {
		std::cout << "      name: " << name << std::endl;
		std::cout << "      suma: " << suma << std::endl;
		std::cout << "      date: " << date << std::endl;
		std::cout << " condition: " << conditions[number] << std::endl;
	}

	// Пул містить внутрішній стан (спільні дані для багатьох клієнтів)
	static Pool_of_conditions conditions;
};
Pool_of_conditions Deposit::conditions;


int main()
{
	srand(time(0));
	// умови, звісно, мали б бути записані у файлах
	Deposit::conditions.AddNewCondition("conditions 0 paragraph 1.. 5");
	Deposit::conditions.AddNewCondition("conditions 1 paragraph 1..10");
	Deposit::conditions.AddNewCondition("conditions 2 paragraph 1..20");
	Deposit::conditions.AddNewCondition("conditions 3 paragraph 1..30");
	Deposit::conditions.AddNewCondition("conditions 4 paragraph 1..40");
	Deposit::conditions.AddNewCondition("conditions 5 paragraph 1..50");
	Deposit::conditions.AddNewCondition("conditions 6 paragraph 1..60");

	std::string names[] = { "Ivan", "Myshko", "Alex", "Ol'ga",
		"Luda", "Luka", "Mariya", "Bogdan", "Kolya", "Valya" };

	std::string dates[] = { "1.10.18", "2.10.18", "4.10.18", "4.10.18",
		"10.10.18", "10.10.18", "12.10.18", "12.10.18", "12.10.18",
		"14.10.18" };

	std::vector<Deposit> base;

	int cnt = Deposit::conditions.count_of_conditions();
	for (int i = 0; i < 10; i++)
		base.push_back(
			{ names[i], 100 + rand() % 1000, dates[i], rand() % cnt });

	for (auto i : base)
		i.Print();

	system("Pause");
	return 0;
}