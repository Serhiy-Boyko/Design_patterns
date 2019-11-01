#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

class Ditch {  // Рів (без варіантів)
public:
	static const int price = 200;
	Ditch() {}
	virtual void Info() {
		std::cout << " The price of the ditch:\t" << price << std::endl;
	};
};

class Walls {  // Стіни
public:
	Walls() {}
	virtual void Info() = 0;
};

class Saxon_Walls : public Walls {
public:
	static const int price = 400;
	Saxon_Walls() {}
	virtual void Info() {
		std::cout << " The price of the Saxon Walls:\t";
		std::cout << price << std::endl;
	};
};

class Teutonic_Walls : public Walls {
public:
	static const int price = 500;
	Teutonic_Walls() {}
	virtual void Info() {
		std::cout<< " The price of the Teutonic Walls:\t"<< price << std::endl;
	};
};

class Gates { // Ворота
public:
	Gates() {}
	virtual void Info() = 0;
};

class Saxon_Gates : public Gates {
public:
	static const int price = 100;
	Saxon_Gates() {}
	virtual void Info() {
		std::cout << " The price of the Saxon Gates:\t"<< price << std::endl;
	};
};

class Teutonic_Gates : public Gates {
public:
	static const int price = 150;
	Teutonic_Gates() {}
	virtual void Info() {
		std::cout<< " The price of the Teutonic Gates:\t"<< price <<std::endl;
	};
};

class Towers { // Towers
public:
	Towers() {}
	virtual void Info() = 0;
};

class Saxon_Towers : public Towers {
public:
	static const int price = 500;
	Saxon_Towers() {}
	virtual void Info() {
		std::cout<< " The price of the Saxon Towers:\t"<< price <<std::endl;
	};
};

class Teutonic_Towers : public Towers {
public:
	static const int price = 750;
	Teutonic_Towers() {}
	virtual void Info() {
		std::cout<< " The price of the Teutonic Towers:\t"<< price <<std::endl;
	};
};

class Citadel { // Citadel
public:
	Citadel() {}
	virtual void Info() = 0;
};

class Saxon_Citadel : public Citadel {
public:
	static const int price = 400;
	Saxon_Citadel() {}
	virtual void Info() {
		std::cout<< " The price of the Saxon Citadel:\t"<< price << std::endl;
	};
};

class Teutonic_Citadel : public Citadel {
public:
	static const int price = 600;
	Teutonic_Citadel() {}
	virtual void Info() {
		std::cout<< " The price of the Teutonic Citadel:\t"<< price <<std::endl;
	};
};

class Lookout_tower { // Lookout_tower (без варіантів)
public:
	static const int price = 100;
	Lookout_tower() {}
	virtual void Info() {
		std::cout << " The price of the lookout_tower:\t"<< price <<std::endl;
	};
};

class Chestnut_tower { // Башта каштеляна (без варіантів)
public:
	static const int price = 100;
	Chestnut_tower() {}
	virtual void Info() {
		std::cout<< " The price of the chestnut_tower:\t"<< price <<std::endl;
	};
};

class Armory { // Зброярня (без варіантів)
public:
	static const int price = 100;
	Armory() {}
	virtual void Info() {
		std::cout << " The price of the armory:\t" << price << std::endl;
	};
};

class Forge { // Ковальня (без варіантів)
public:
	static const int price = 100;
	Forge() {}
	virtual void Info() {
		std::cout << " The price of the forge:\t" << price << std::endl;
	};
};

class Castle {
protected:
	Ditch *ditch = nullptr;
	Walls *walls = nullptr;
	Gates *gates = nullptr;
	Towers *towers = nullptr;
	Citadel *citadel = nullptr;
	Lookout_tower *lookout_tower = nullptr;
	Chestnut_tower *chestnut_tower = nullptr;
	Armory *armory = nullptr;
	Forge *forge = nullptr;
	std::string castleName;
	std::string castleType;
public:
	Castle(std::string name, std::string type) 
		:castleName(name), castleType(type) {
		std::cout << " Start building of " << castleName;
	}
	void Info() {
		std::cout << castleType << " " << castleName << std::endl;
	};

	friend class Builder;
	friend class Teutonic_Builder;
	friend class Saxon_Builder;
};

class Teutonic_Castle : public Castle {
public:
	Teutonic_Castle(std::string name) : Castle(name, "Teutonic Castle") {
		std::cout << " - " << castleType << std::endl;
	}
};

class Saxon_Castle : public Castle {
public:
	Saxon_Castle(std::string name) : Castle(name, "Saxon Castle") {
		std::cout << " - " << castleType << std::endl;
	}
};

/* class Builder (pattern Builder) - окремий клас
для створення деякого об'єкта покроково */

class Builder {
protected:
	Castle *p;
public:
	Builder() : p(nullptr) {}
	virtual Castle *Build_Castle(std::string castleName) = 0;
	/*virtual*/ void dig_Ditch() { p->ditch = new Ditch(); }
	virtual void Build_Walls() {}
	virtual void Build_Gates() {}
	virtual void Build_Towers() {}
	virtual void Build_Citadel() {}
	/*virtual*/ void Build_Lookout_tower() { 
		p->lookout_tower = new Lookout_tower(); 
	}
	/*virtual*/ void Build_Chestnut_tower() { 
		p->chestnut_tower = new Chestnut_tower(); 
	}
	/*virtual*/ void Build_Armory() { p->armory = new Armory(); }
	/*virtual*/ void Build_Forge() { p->forge = new Forge(); }
	~Builder() { delete p; }
};

class Saxon_Builder : public Builder {
public:
	virtual Castle *Build_Castle(std::string castleName) {
		p = new Saxon_Castle(castleName);
		return p;
	}
	//virtual void dig_Ditch() {}
	virtual void Build_Walls() { p->walls = new Saxon_Walls(); }
	virtual void Build_Gates() { p->gates = new Saxon_Gates(); }
	virtual void Build_Towers() { p->towers = new Saxon_Towers(); }
	virtual void Build_Citadel() { p->citadel = new Saxon_Citadel(); }
	//virtual void Build_Lookout_tower() {}
	//virtual void Build_Chestnut_tower() {}
	//virtual void Build_Armory() {}
	//virtual void Build_Forge() {}
};

class Teutonic_Builder : public Builder {
public:
	virtual Castle *Build_Castle(std::string castleName) {
		p = new Teutonic_Castle(castleName);
		return p;
	}
	//virtual void dig_Ditch() {}
	virtual void Build_Walls() { p->walls = new Teutonic_Walls(); }
	virtual void Build_Gates() { p->gates = new Teutonic_Gates(); }
	virtual void Build_Towers() { p->towers = new Teutonic_Towers(); }
	virtual void Build_Citadel() { p->citadel = new Teutonic_Citadel(); }
	//virtual void Build_Lookout_tower() {}
	//virtual void Build_Chestnut_tower() {}
	//virtual void Build_Armory() {}
	//virtual void Build_Forge() {}
};

/* class Director - окремий клас
для покрокової постановки задач будівельникам */
class Director {
public:
	virtual Castle *Build_Castle(Builder &fact, std::string castleName) {
		Castle *p = fact.Build_Castle(castleName);
		Sleep(400);
		std::cout << " Diging of Ditch" << std::endl;
		fact.dig_Ditch();
		Sleep(400);
		std::cout << " Building of Walls" << std::endl;
		fact.Build_Walls();
		Sleep(400);
		std::cout << " Building of Gates" << std::endl;
		fact.Build_Gates();
		Sleep(400);
		std::cout << " Building of Towers" << std::endl;
		fact.Build_Towers();
		Sleep(400);
		std::cout << " Building of Citadel" << std::endl;
		fact.Build_Citadel();
		Sleep(400);
		std::cout << " Building of Lookout tower" << std::endl;
		fact.Build_Armory();
		Sleep(400);
		std::cout << " Building of Chestnut tower" << std::endl;
		fact.Build_Chestnut_tower();
		Sleep(400);
		std::cout << " Building of Armory" << std::endl;
		fact.Build_Armory();
		Sleep(400);
		std::cout << " Building of Forge" << std::endl;
		fact.Build_Forge();
		Sleep(400);
		std::cout << std::endl;
		return p;
	}
};

int main() {
	Saxon_Builder SBuilder;
	Teutonic_Builder TBuilder;
	Director dir;

	Castle *A = dir.Build_Castle(SBuilder, "York");
	Castle *B = dir.Build_Castle(TBuilder, "Riga");

	system("pause");
	return 0;
}
