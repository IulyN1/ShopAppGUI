#pragma once
#include <vector>
#include <map>
#include "Produs.h"
#include "TemplateVector.h"
using std::vector;
using std::map;

class RepoException {
	string msg;

public:
	// Functie de initializare a clasei de exceptii pentru repository
	// m - string
	RepoException(string m) :msg{ m } {};

	// Functie care returneaza mesajul de eroare in caz de exceptie
	string get_msg();
};

class Repo {
public:
	// Functie pur abstracta de adaugare produs in repo
	// p - obiect Produs
	virtual void add(const Produs& p) = 0;

	// Functie pur abstracta de afisare a tuturor produselor din repo
	virtual const vector<Produs> get_all() const = 0;

	// Functie pur abstracta de cautare produs in repo
	// id - numar intreg
	virtual const Produs& cauta(int id) const = 0;

	// Functie pur abstracta de modificare produs in repo
	// id - numar intreg
	// produs - obiect Produs
	virtual void modifica(int id, const Produs& produs) = 0;

	// Functie pur abstracta de stergere produs din repo
	// id - numar intreg
	virtual void sterge(int id) = 0;

	// Destructorul default al clasei de repository abstract
	virtual ~Repo() = default;
};

class RepoLab: public Repo {
private:
	double prob;
	map<int,Produs> dict;
public:
	//   Functie care genereaza un numar random intre 0 si 100 si verifica daca este mai mare decat probabilitatea
	// fiind luat proportional si arunca exceptie daca se intampla
	void get_random() const;

	// Constructorul clasei de RepoLab mostenit din Repo abstract
	// prob - numar real intre 0 si 1
	RepoLab(double prob) :prob{ prob } {}

	// Functie de adaugare produs in repo suprascrisa
	// p - obiect Produs
	void add(const Produs& p) override;

	// Functie care returneaza produsele din repo suprascrisa
	const vector<Produs> get_all() const override;

	// Functie de cautare produs in repo suprascrisa
	// id - numar intreg
	const Produs& cauta(int id) const override;

	// Functie de modificare produs in repo suprascrisa
	// id - numar intreg
	// produs - obiect Produs
	void modifica(int id, const Produs& produs) override;

	// Functie de stergere produs din repo suprascrisa
	// id - numar intreg
	void sterge(int id) override;
};

class ProdusRepo : public Repo
{
private:
	vector<Produs> produse;

public:
	// Functie care nu permite copierea unui repository 
	// ot - o instanta a clasei ProdusRepo
	ProdusRepo(const ProdusRepo& ot) = delete;

	// Functie de initializare default a repo-ului
	ProdusRepo() = default;

	// Functie care adauga un produs in repository
	// produs - obiect Produs
	// arunca exceptie daca exista deja produsul in repository
	void add(const Produs& produs) override;

	// Functie care returneaza toate produsele din repository
	const vector<Produs> get_all() const override;

	// Functie care cauta un produs dupa id in repository
	// id - numar intreg
	// arunca exceptie daca nu exista produsul in repository
	const Produs& cauta(int id) const override;

	// Functie care modifica un produs dupa id din repository
	// id - numar intreg
	// produs - obiect Produs
	// arunca exceptie daca nu exista produsul in repository
	void modifica(int id, const Produs& produs) override;

	// Functie care sterge un produs dupa id in repository
	// id - numar intreg
	// arunca exceptie daca nu exista produsul in repository
	void sterge(int id) override;

	// Destructorul default al clasei ProduRepo
	//virtual ~ProdusRepo() = default;
};

class ProdusRepoFile :public ProdusRepo {
private:
	string filename;

	// Functie care preia datele din fisier
	// filename - string
	void loadFromFile(const string& filename);

	// Functie care scrie date in fisier
	// filename - string
	void storeToFile(const string& filename);
public:

	// Constructorul clasei de Repository cu fisiere care mosteneste din Repository-ul de baza
	// filename - string
	ProdusRepoFile(const string& filename) :ProdusRepo(), filename{ filename }{
		loadFromFile(filename);
	}

	// Functia de adaugare a unui produs suprascrisa pentru fisiere
	// p - referinta la un obiect de tip Produs
	void add(const Produs& p) override {
		ProdusRepo::add(p);
		storeToFile(filename);
	}

	// Functie de stergere a unui produs suprascrisa pentru fisiere
	// id - numar intreg
	void sterge(int id) override {
		ProdusRepo::sterge(id);
		storeToFile(filename);
	}

	// Functie de modificare a unui produs suprascrisa pentru fisiere
	// id - numar intreg
	// p - referinta la un obiect de tip Produs
	void modifica(int id,const Produs& p) override {
		ProdusRepo::modifica(id,p);
		storeToFile(filename);
	}
};