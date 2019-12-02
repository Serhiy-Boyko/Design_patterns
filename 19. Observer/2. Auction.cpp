/* Task 2. Реалізувати торги на аукціоні, де учасники щоразу піднімають ціну на визначений відсоток. */
#include <iostream>
#include <string>
#include <vector>

class Lot{ // учасник аукціону
	std::string name; 
	size_t price;     // початкова ціна
public:
	Lot(std::string n, int p) : name(n), price(p) {}

	void Print() {
		std::cout << " Lot: " << name << " price: " << price << std::endl;
	}

	std::string getname() { return name; }
	int getprice() { return price; };
	void incprice() { price*=1.1; }
};

class Auctioneer;

class Bidder { // учасник аукціону (Observer)
protected:
	std::string name;
	size_t cash;
	Auctioneer *auctioneer;
public:
	Bidder(std::string n, int c, Auctioneer *a);

	void Print() {
		std::cout << " Bidder: " << name << " cash: " << cash << std::endl;
	}

	std::string getname() { return name; }
	size_t getcash() { return cash; };

	virtual void update(Lot *l);
};

/* Ведучий торгів (Subject), оголошує лот і веде торги,
   збільшуючи щоразу ціну на 10 % */
class Auctioneer {
	Lot* lot; // Лот
	std::string name = ""; // ім'я учасника, що запропонував останню ціну
	std::vector<Bidder*> Bidders; // список учасників торгів
public:
	void addObserver(Bidder *obs) { Bidders.push_back(obs); }

	void takeLot(Lot *l) { lot = l; }

	void offerLot() { // notify
		std::cout << "-------------------------------------" << std::endl;
		std::cout << "Auctioneer: ";
		lot->Print();
		for (int i = 0; i < Bidders.size(); ++i)
			Bidders[i]->update(lot);
	}

	void takePropose(std::string n) { 
		name = n;
		lot->incprice(); 
	}
	size_t getprice() { return lot->getprice(); }
	std::string getname() { return name; }

	void Result() { 
		std::cout << "======================================" << std::endl;
		std::cout << "Auctioneer: congratulations the " << name << "!\n";
		lot->Print();
	}
};

Bidder::Bidder(std::string n, int c, Auctioneer *a)
	: name(n), cash(c), auctioneer(a) 
{
	auctioneer->addObserver(this);
}

void Bidder::update(Lot *lot) {
	if (auctioneer->getname() != name && lot->getprice()*1.2 < cash) {
		std::cout << " Bidder: " << name << " increase! " << std::endl;
		auctioneer->takePropose(name);
	}
}

int main() {
	Auctioneer auctioneer;
	Bidder bidder1("Smith", 6000, &auctioneer);
	Bidder bidder2("O'Nil", 8000, &auctioneer);
	Bidder bidder3("McLaut", 12000, &auctioneer);

	size_t price = 2000;
	auctioneer.takeLot(new Lot("pen of Van Damme", price));
	size_t nextprice = 0;
	do {
		if (nextprice > price)
			price = nextprice;
		auctioneer.offerLot();
		nextprice = auctioneer.getprice();
	} while (nextprice > price);

	auctioneer.Result();
	system("pause");
	return 0;
}
