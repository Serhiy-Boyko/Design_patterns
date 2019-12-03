#include <iostream>

/* Task. Трасформер може перебувати у двох станах – робота і літака. Робот може ходити і бігати, але не може літати. Літак може літати, але не може ходити і бігати.*/
class Transformer {
public:
	//  States 
	class State {
	public:
		virtual void run(Transformer*) {
			std::cout << "  Run: Can not run " << std::endl;
		}

		virtual void step(Transformer*) {
			std::cout << " Step: Can not step " << std::endl;
		}

		virtual void fly(Transformer*) {
			std::cout << "  Fly: Can not fly " << std::endl;
		}

		virtual void TransformToRobot(Transformer *t) {
			std::cout << " Transform to Robot: You already is robot \n";
		}

		virtual void TransformToPlane(Transformer *t) {
			std::cout << " Transform to Plane: You already is plane \n";
		}
	};

	// **************************************************
	class Robot : public State {
	public:
		static Robot *getInstance() {
			static Robot instance;
			return &instance;
		}

		virtual void run(Transformer*) {
			std::cout << "  Run: Robot run" << std::endl;
		}

		virtual void step(Transformer*) {
			std::cout << " Step: Robot step" << std::endl;
		}

		virtual void TransformToPlane(Transformer *t) {
			std::cout << " Transform to Plane: Transform to plane \n";
			t->changeState(Plane::getInstance());
		}
	};

	// **************************************************
	class Plane : public State {
	public:
		static Plane *getInstance() {
			static Plane instance;
			return &instance;
		}

		virtual void fly(Transformer*) {
			std::cout << "  Fly: Plane fly " << std::endl;
		}

		virtual void TransformToRobot(Transformer *t) {
			std::cout << " Transform to Robot: Transform to robot " << std::endl;
			t->changeState(Robot::getInstance());
		}
	};

private:
	int num;
	State *m_state;

	void changeState(State* newState) { m_state = newState; }
public:
	explicit Transformer(int n) : num(n), m_state(Robot::getInstance()) {}

	void run() { m_state->run(this); }

	void step() { m_state->step(this); }

	void fly() { m_state->fly(this); }

	void TransformToRobot() { m_state->TransformToRobot(this); }

	void TransformToPlane() { m_state->TransformToPlane(this); }
};

int main()
{
	Transformer T(101); // початковий стан - робот
	T.step();
	T.step();
	T.run();
	T.TransformToPlane(); // трансформування в літак
	T.fly();
	T.step(); // літак не може зробити крок
	T.fly();

	T.TransformToRobot(); // трансформування в робота
	T.TransformToRobot(); // робот вже є роботом
	system("pause");
	return 0;
}
