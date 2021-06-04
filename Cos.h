#pragma once
#include "Produs.h"
#include <vector>
#include "ProdusRepo.h"
#include "Observer.h"

using std::vector;

class CosException {
	string msg;

public:
	// Functie de initializare a clasei de exceptii pentru cos
	// m - string
	CosException(string m) :msg{ m } {};

	// Functie care returneaza mesajul de eroare in caz de exceptie
	string get_msg();
};


class Cos: public Observable
{
private:
	vector<Produs> in_cos;
	Repo& repo;
public:
	// Constructorul clasei Cos
	// repo - referinta la o instanta a repository-ului de produse ProdusRepo
	Cos(Repo& repo) noexcept :repo{ repo } {}

	// Functie care adauga un produs in cos
	// produs - obiect de tip Produs
	void adauga(const Produs& produs);

	// Functie care modifica un produs in cos daca a fost modificat din lista de produse
	// id - numar intreg
	// p - obiect de tip Produse
	void modifica(int id, const Produs& p);

	// Functie care sterge un produs din cos daca a fost sters din lista de produse
	// id - numar intreg
	void sterge(int id);

	// Functie care returneaza toate produsele din cos
	const vector<Produs>& get_all() const noexcept;

	// Functie care goleste cosul de produse
	void goleste() noexcept;

	// Functie care returneaza costul total al produselor din cos
	float checkout() noexcept;

	// Functie care exporta continutul cosului intr-un fisier CSV
	// filename - string reprezentand numele fisierului CSV
	void exportCSV(const string& filename);

	// Functie care adauga un numar fixat de produse in cos, luate aleator
	// nr - numar intreg
	void genereaza(int nr);
};

