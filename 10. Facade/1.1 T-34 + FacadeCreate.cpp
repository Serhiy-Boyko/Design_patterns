#include <iostream>

class Radio {
public:
	virtual bool Call(int d) = 0;
};

class P9 : public Radio {
	static int max_distance;
public:
	virtual bool Call(int d) {
		if (d < max_distance) {
			std::cout << " Can talk " << std::endl;
			return 1;
		}
		else {
			std::cout << " Distance too long " << std::endl;
			return 0;
		}
	}
};

int P9::max_distance = 5000;

class PM9 : public Radio {
	static int max_distance;
public:
	virtual bool Call(int d) {
		if (d < max_distance) {
			std::cout << " Can talk " << std::endl;
			return 1;
		}
		else {
			std::cout << " Distance too long " << std::endl;
			return 0;
		}
	}
};

int PM9::max_distance = 7000;

// -----------------------------------------------------------------

class Engine {
protected:
	int speed;
public:
	virtual int Clutch(int num) = 0;
};

class B2 : public Engine {
public:
	virtual int Clutch(int num) {
		if (num < 4)
			speed = num * 8;
		else
			speed = 32;
		std::cout << " speed: " << speed << std::endl;
		return speed;
	}
};

class B234 : public Engine {
public:
	virtual int Clutch(int num) {
		if (num < 4)
			speed = num * 10;
		else
			speed = 40;
		std::cout << " speed: " << speed << std::endl;
		return speed;
	}
};
// -----------------------------------------------------------------

class Cannon {
protected:
	int count_of_shot = 0;
public:
	virtual int Time(int count) = 0;
	int getTotalShot() { return count_of_shot; }
};

class Zis34 : public Cannon {
	static int shots_per_min;
public:
	virtual int Time(int count) {
		count_of_shot += count;
		int time = count * 60 / shots_per_min;
		std::cout << " time for shots: " << time << std::endl;
		return time;
	}
};
int Zis34::shots_per_min = 6;

class F34 : public Cannon {
	static int shots_per_min;
public:
	virtual int Time(int count) {
		count_of_shot += count;
		int time = count * 60 / shots_per_min;
		std::cout << " time for shots: " << time << std::endl;
		return time;
	}
};
int F34::shots_per_min = 5;

// -----------------------------------------------------------------
class T34 {
	Engine *En;
	Radio *Ra;
	Cannon *Ca;
	int numgear;
public:
	T34(Engine *en, Radio *ra, Cannon *ca) : 
		En(en), Ra(ra), Ca(ca), numgear(0) {}

	// З точки зору управління, це фасад для модулів
	void Fast() { if (numgear < 5) En->Clutch(++numgear); }
	void Slowly() { if (numgear > 1) En->Clutch(--numgear); }
	void Go() { En->Clutch(numgear); }

	bool Talk(int d) { return Ra->Call(d); };

	int Shot(int cnt) { return Ca->Time(cnt); }
};

class FacadeCreateT34 {
public:
	static T34 &create40() {
		T34 Tank(new B2, new P9, new Zis34);
		return Tank;
	}

	static T34 &create42() {
		T34 Tank(new B234, new PM9, new F34);
		return Tank;
	}
};

int main()
{
	T34 N317 = FacadeCreateT34::create40();
	// T34 N317(new B2, new P9, new Zis34);
	N317.Fast();
	N317.Fast();
	N317.Fast();
	N317.Go();
	N317.Slowly();
	N317.Slowly();
	N317.Slowly();
	N317.Shot(5);

	// T34 N318(new B234, new PM9, new F34);
	T34 N318 = FacadeCreateT34::create42();
	N318.Talk(4000);
	N318.Talk(14000);
	N318.Shot(6);
	system("Pause");
	return 0;
}