#pragma once
#include <string>
#include <iostream>
using std::string;

class Produs
{
private:
	int id_produs;
	string nume;
	string tip;
	float pret;
	string prod;

public:
	// Functie de initializare a unui produs
	// id_produs - numar intreg
	// nume - string
	// tip - string
	// pret - numar real
	// prod - string
	Produs(int id_produs, string nume, string tip, float pret, string prod) :id_produs{ id_produs }, nume { nume }, 
		tip{ tip }, pret{ pret }, prod{ prod }{};

	Produs() = default;

	// Functie getter care returneaza id-ul produsului
	int get_id() const noexcept;

	// Functie getter care returneaza numele produsului
	const string& get_nume() const noexcept;

	// Functie getter care returneaza tipul produsului
	const string& get_tip() const noexcept;

	// Functie getter care returneaza pretul produsului
	float get_pret() const noexcept;

	// Functie getter care returneaza producatorul produsului
	const string& get_prod() const noexcept;

	// Functie setter care seteaza numele produsului
	void set_nume(const string& name);

	// Functie setter care seteaza tipul produsului
	void set_tip(const string& type);

	// Functie setter care seteaza pretul produsului
	void set_pret(float price) noexcept;

	// Functie setter care seteaza producatorul produsului
	void set_prod(const string& produc);
	
	// Functie de copiere a unui produs
	// ot - obiect Produs
	Produs(const Produs& ot) :id_produs{ ot.id_produs }, nume{ ot.nume }, tip{ ot.tip }, pret{ ot.pret }, 
		prod{ ot.prod }{ 
		//std::cout << "Copy constructor called\n"; 
	};
};
