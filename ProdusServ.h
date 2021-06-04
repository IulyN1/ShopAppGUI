#pragma once
#include <string>
#include "Produs.h"
#include "ProdusRepo.h"
#include "Validator.h"
#include "Cos.h"
#include "ProduseDTO.h"
#include <unordered_map>
#include "ActiuneUndo.h"
using std::unordered_map;
using std::string;
using std::vector;
using std::unique_ptr;

class SrvException {
	string msg;

public:
	// Functie de initializare a clasei de exceptii pentru service
	// m - string
	SrvException(string m) :msg{ m } {};

	// Functie care returneaza mesajul de eroare in caz de exceptie
	string get_msg();
};

class ProdusServ
{
private:
	Cos& cos;
	Repo& repo;
	Validator& valid;
	vector<unique_ptr<ActiuneUndo>> undoActions;

public:
	// Functie de initializare a service-ului de produse
	// repo - referinta la o instanta a clasei ProdusRepo
	// valid - referinta la o instanta a clasei Validator
	ProdusServ(Repo& repo, Validator& valid, Cos& cos) :repo{ repo }, valid{ valid }, cos{ cos } {};

	// Functie care nu permite copierea service-ului
	// ot - referinta la o instanta a clasei ProdusServ
	ProdusServ(const ProdusServ& ot) = delete;

	// Functie care reprezinta constructorul default al service-ului
	ProdusServ() = default;

	// Functie care permite adaugarea unui produs pe baza input-ului utilizatorului
	// id - numar intreg
	// nume - string
	// tip - string
	// pret - numar real
	// prod - string
	void add_produs(int id, const string& nume, const string& tip, float pret, const string& prod);

	// Functie care returneaza toate obiectele din repository
	const vector<Produs> get_all() const;

	// Functie care permite cautarea unui produs pe baza id-ului
	// id - numar intreg
	// returneaza produsul corespunzator daca s-a gasit
	const Produs& cauta_produs(int id) const;

	// Functie care permite modificarea unui produs pe baza unui id si a datelor de la input-ul utilizatorului
	// id - numar intreg
	// nume - string
	// tip - string
	// pret - numar real
	// prod - string
	void modifica_produs(int id, const string& nume, const string& tip, float pret, const string& prod);

	// Functie care permite stergerea unui produs pe baza id-ului
	// id - numar intreg
	void sterge_produs(int id);

	// Functie care filreaza produsele dupa criteriul dat de valoare
	// valoare - numar real
	// returneaza lista produselor care respecta criteriul
	const vector<Produs> filtreaza_float(float valoare);

	// Functie care filreaza produsele dupa criteriul dat de valoare
	// opt - string ( 2-nume, 3-producator )
	// valoare - string
	// returneaza lista produselor care respecta criteriul
	const vector<Produs> filtreaza_str(const string& opt, const string& valoare);

	// Functie care sorteaza produsele dupa o optiune data
	// opt - string ( 1-nume, 2-pret, 3-nume+tip )
	// returneaza lista produselor sortate
	const vector<Produs> sorteaza(const string& opt);

	// Functie de adaugare a unui produs in cos dupa id
	// id - numar intreg
	void adauga_cos(int id);

	// Functie care returneaza totalul produselor din cos
	float total_cos();

	// Functie care returneaza toate produsele din cos
	const vector<Produs>& get_all_cos() const;

	// Functie care goleste cosul de produse
	void golire_cos();

	// Functie care adauga un numar fixat de produse in cos, luate aleator
	// nr - numar intreg
	void generare_cos(int nr);

	// Functie care da export la cosul de produse intr-un fisier CSV
	// filename - string reprezentand numele fisierului CSV
	void export_cos(const string& filename);

	// Functie care creeaza un raport al produselor spunand tipul si numarul de produse de acel tip
	unordered_map <string, ProduseDTO> raport();

	// Functie care realizeaza undo
	void undo();
};


