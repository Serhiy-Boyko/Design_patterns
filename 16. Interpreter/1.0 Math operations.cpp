#include <iostream>
#include <string>
#include <map>
// інтерпритатор математичних операцій + та - без парсера

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
class Expression {
public:
	virtual int Interpret(Context context) { return 0; }
};

// термінальний вираз
class Variable : public Expression {
	std::string exp;
public:
	Variable(std::string e) : exp(e) {}
	int Interpret(Context context) { return context.GetVariable(exp); }
};

// нетермінальний вираз для додавання
class AddExpression : public Expression {
	Expression *lExpression;
	Expression *rExpression;
public:
	AddExpression(Expression *left, Expression *right) :
		lExpression(left), rExpression(right) {}

	int Interpret(Context c) {
		return lExpression->Interpret(c) + rExpression->Interpret(c);
	}
};

// нетермінальний вираз для віднімання
class SubtractExpression : public Expression {
	Expression *lExpression;
	Expression *rExpression;
public:
	SubtractExpression(Expression *left, Expression *right) :
		lExpression(left), rExpression(right) {}

	int Interpret(Context c) {
		return lExpression->Interpret(c) - rExpression->Interpret(c);
	}
};

int main()
{
	Context context;
	// визначаємо перелік змінних
	int x = 5;
	int y = 8;
	int z = 2;
	
	// додаємо змінні в контекст
	context.SetVariable("x", x);
	context.SetVariable("y", y);
	context.SetVariable("z", z);
	context.Print();

	/* для кожної операції виразу x + y - z створюється окремий об'єкт,
		бо парсерсінг у інтрепритаторі не передбачений  */
	Expression *expression = new SubtractExpression(
		new AddExpression(new Variable("x"), new Variable("y")),
		new Variable("z")
	);

	int result = expression->Interpret(context);
	std::cout << " result: " << result << std::endl;

	system("Pause");
	return 0;
}