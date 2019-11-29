#include <iostream>
#include <string>
#include <vector>
#include <map>
// інтерпритатор математичних операцій з парсером

// клас збереження імен змінних та їх значень
class Context {
	std::map<std::string, int> variables;
public:
	int GetVariable(std::string name) { return variables[name]; }

	void SetVariable(std::string name, int value) {
		if (variables.find(name) != variables.end())
			variables[name] = value;
		else
			variables.insert({ name, value });
	}

	void Print() {
		std::cout << " Context print: " << std::endl;
		for (auto it : variables)
			std::cout << it.first << " = " << it.second << std::endl;
		std::cout << std::endl;
	}
};

// базовий клас інтерпритатора
class BInterpreter {
protected:
	Context *context;
public:
	BInterpreter(Context *c) : context(c) {}
	virtual int Interpret(std::string &exp) = 0;
};

// термінальний вираз
class Variable : public BInterpreter {
public:
	Variable(Context *c) : BInterpreter(c) {}

	int Interpret(std::string &exp) {
		int i;
		for (i = 0; i < exp.length(); i++)
			if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
				break;
		std::string e = exp.substr(0, i);
		exp = exp.substr(i, exp.length());
		return context->GetVariable(e);
	}
};

// нетермінальний вираз
class EInterpreter : public BInterpreter {
public:
	EInterpreter(Context *c) : BInterpreter(c) {}

	virtual int Interpret(std::string &exp) {
		std::vector <double> members;
		Variable *v = new Variable(context);
		members.push_back(v->Interpret(exp));
		char z;
		while (exp.length() > 0) {
			z = exp[0];
			exp = exp.substr(1, exp.length());
			switch (z) {
			case '+': members.push_back(v->Interpret(exp)); break;
			case '-': members.push_back(-v->Interpret(exp)); break;
			case '*': members[members.size() - 1] *= v->Interpret(exp); break;
			case '/': members[members.size() - 1] /= v->Interpret(exp); break;
			}
		}
		int res = members[0];
		for (int i = 1; i < members.size(); i++)
			res += members[i];
		return res;
	}
};

int main()
{
	Context *context = new Context;
	// визначаємо перелік змінних
	int x = 5;
	int y = 8;
	int z = 2;

	// додаємо змінні в контекст
	context->SetVariable("x", x);
	context->SetVariable("y", y);
	context->SetVariable("z", z);
	context->Print();

	// створюємо об'єкт для інтерпритації з контекстом
	BInterpreter *p = new EInterpreter(context);

	//string exp = "x+x+y+y";
	std::string exp = "x*x+y*y";

	std::cout << exp << " = ";
	int result = p->Interpret(exp);
	std::cout << result << std::endl;
	system("Pause");
	return 0;
}