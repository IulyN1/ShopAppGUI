#pragma once
#include "Produs.h"

class ValidException{
	string msg;
public:
	// Functie de initializare a clasei de exceptii pentru validator
	// m - string
	ValidException(string m) :msg{ m } {};

	// Functie care returneaza mesajul de eroare in caz de exceptie
	string get_msg();
};

class Validator
{
public:

	// Functie care valideaza campurile unui produs
	// p - referinta la o instanta a unui obiect Produs
	const void valideaza(const Produs& p) const;
};

