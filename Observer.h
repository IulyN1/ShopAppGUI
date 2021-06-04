#pragma once
#include <algorithm>
#include <vector>
using std::vector;

class Observer {
public:
	// Functie pur virtuala de update a Observerului
	virtual void update() = 0;
};

class Observable {
	vector<Observer*> interesati;
protected:
	// Functie care apeleaza update pentru fiecare obiect observat
	void notify() {
		for (auto obs : interesati) {
			obs->update();
		}
	}
public:
	// Functie care adauga un observer
	// o - pointer la obiect de tip Observer
	void addObserver(Observer* o) {
		interesati.push_back(o);
	}

	// Functie care elimina un observer
	// o - pointer la obiect de tip Observer
	void removeObserver(Observer* o) {
		interesati.erase(std::remove(interesati.begin(), interesati.end(), o), interesati.end());
	}
};