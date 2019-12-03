#include <iostream>

/* Task. У людини може бути 4 стани: здорова, хвора, у комі, мертва. У кожного стану своя активність. Здорова людина може захворіти, але не впасти в кому і не померти. Хворе може і одужати, і впасти в кому, і померти. З коми людина повертається у хворий стан або помирає. Мертва лишається мертвою. */

class Man {
public:
	//  States 
	class state {
	public:
		virtual void activity() = 0;
		virtual void to_healthy(Man *t) = 0;
		virtual void to_ill(Man *t) = 0;
		virtual void to_coma(Man *t) = 0;
		virtual void to_die(Man *t) = 0;
	};

	// **************************************************
	class healthy : public state {
	public:
		static healthy *getInstance() {
			static healthy instance;
			return &instance;
		}

		virtual void activity() {
			std::cout << " Healthy: Go, run, jump! " << std::endl;
		}

		virtual void to_healthy(Man *t) {
			std::cout << " Healthy: The man already is healthy! \n";
		}

		virtual void to_ill(Man *t) {
			std::cout << " Healthy: The man to fall to ill... \n";
			t->changeState(ill::getInstance());
		}

		virtual void to_coma(Man *t) {
			std::cout << " Healthy: The healthy man can't fall to coma! \n";
		}

		virtual void to_die(Man *t) {
			std::cout << " Healthy: The healthy man can't to die! \n";
		}
	};

	// **************************************************
	class ill : public state {
	public:
		static ill *getInstance() {
			static ill instance;
			return &instance;
		}

		virtual void activity() {
			std::cout << "     Ill: Lie in bed, drink medicine \n";
		}

		virtual void to_healthy(Man *t) {
			std::cout << "     Ill: The man is recovered! \n";
			t->changeState(healthy::getInstance());
		}

		virtual void to_ill(Man *t) {
			std::cout << "     Ill: The man already is ill! \n";
		}

		virtual void to_coma(Man *t) {
			std::cout << "     Ill: The man is fall to coma... \n";
			t->changeState(comatose::getInstance());
		}

		virtual void to_die(Man *t) {
			std::cout << "     Ill: The man is die \n";
			t->changeState(dead::getInstance());
		}
	};
	// **************************************************
	class comatose : public state {
	public:
		static comatose *getInstance() {
			static comatose instance;
			return &instance;
		}

		virtual void activity() {
			std::cout << " Comatose: Lie in hospital with droppers... \n";
		}

		virtual void to_healthy(Man *t) {
			std::cout << " Comatose: The man can't recovered! \n";
		}

		virtual void to_ill(Man *t) {
			std::cout << " Comatose: The man is came out of the coma! \n";
			t->changeState(ill::getInstance());
		}

		virtual void to_coma(Man *t) {
			std::cout << " Comatose: The man already is comatose... \n";
		}

		virtual void to_die(Man *t) {
			std::cout << " Comatose: The man is die \n";
			t->changeState(dead::getInstance());
		}
	};

	// **************************************************
	class dead : public state {
	public:
		static dead *getInstance() {
			static dead instance;
			return &instance;
		}

		virtual void activity() {
			std::cout << " Dead: Lie and not to breath... \n";
		}

		virtual void to_healthy(Man *t) {
			std::cout << " Dead: The dead man can't come alive again! \n";
		}

		virtual void to_ill(Man *t) {
			std::cout << " Dead: The dead man can't come alive again! \n";
		}

		virtual void to_coma(Man *t) {
			std::cout << " Dead: The dead man can't come alive again! \n";
		}

		virtual void to_die(Man *t) {
			std::cout << " Dead: The dead man can't dead again! \n";
		}
	};

private:
	state *m_state;

	void changeState(state* newState) { m_state = newState; }
public:
	explicit Man() : m_state(healthy::getInstance()) {}

	virtual void activity() { m_state->activity(); };
	virtual void to_healthy() { m_state->to_healthy(this); };;
	virtual void to_ill() { m_state->to_ill(this); };;
	virtual void to_coma() { m_state->to_coma(this); };;
	virtual void to_die() { m_state->to_die(this); };;
};

int main()
{
	Man A; // початковий стан - здоровий
	A.activity();
	A.activity();

	A.to_ill();
	A.activity();

	A.to_healthy();
	A.activity();
	A.activity();
	std::cout << '\n';

	A.to_ill();
	A.activity();
	A.to_coma();
	A.to_healthy();
	A.activity();
	A.to_ill();
	A.activity();
	A.to_healthy();
	A.activity();
	A.activity();
	std::cout << '\n';

	A.to_ill();
	A.activity();
	A.to_coma();
	A.activity();
	A.to_die();
	A.activity();
	std::cout << '\n';
	A.to_healthy();
	A.to_ill();
	A.to_coma();
	A.to_die();

	system("pause");
	return 0;
}
