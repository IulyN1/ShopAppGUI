#pragma once
#include "ProdusServ.h"
class UI
{
	ProdusServ& srv;

public:
	// Functie care initializeaza clasa UI
	// srv - referinta la o instanta a clasei ProdusServ
	UI(ProdusServ& srv) noexcept :srv{ srv } {};

	// Functie care ruleaza programul principal
	void start();

	// Functie care afiseaza meniul principal
	void menu();

	// Functie care ruleaza comanda de afisare a produselor
	void afisare_UI();

	// Functie care ruleaza comanda de adaugare a unui produs
	// id - referinta la un numar intreg
	void adauga_UI(int& id);

	// Functie care ruleaza comanda de cautare a unui produs
	void cauta_UI();

	// Functie care ruleaza comanda de modificare a unui produs
	void modifica_UI();

	// Functie care ruleaza comanda de stergere a unui produs
	void sterge_UI();

	// Functie care ruleaza comanda de filtrare a produselor
	// opt - numar intreg
	void filtrare_UI(const string& opt);

	// Functie care ruleaza comanda de sortare a produselor
	// opt - numar intreg
	void sortare_UI(const string& opt);

	// Functie care ruleaza comanda de adaugare produs in cos
	void adauga_cos_UI();

	// Functie care ruleaza comanda de afisare a produselor din cos
	void afiseaza_cos_UI();

	// Functie care ruleaza comanda de golire a cosului
	void goleste_cos_UI();

	// Functie care ruleaza comanda de populare a cosului cu produse aleator
	void genereaza_cos_UI();

	// Functie care ruleaza comanda de export a cosului in fisier CSV
	void export_cos_UI();

	// Functie care ruleaza comanda de raport
	void raport_UI();

	// Functie care ruleaza comanda de undo
	void undo_UI();
};

