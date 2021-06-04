#pragma once
#include "Produs.h"
#include "ProdusRepo.h"

class ActiuneUndo
{
public:
	// Metoda pur virtuala care lasa descendentiilor implementarea functiei care face undo
	virtual void doUndo() = 0;

	// Destructorul default al clasei de baza ActiuneUndo
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Produs p;
	Repo& repo;
public:

	// Constructorul clasei UndoAdauga derivate din ActiuneUndo
	// repo - referinta la un repository-ul de fisiere
	// p - produsul adaugat care prin undo va fi sters
	UndoAdauga(Repo& repo, const Produs& p) : repo{ repo }, p{ p }{}

	// Functia care face undo suprascrisa pentru UndoAdauga
	void doUndo() override {
		repo.sterge(p.get_id());
	}
};

class UndoSterge : public ActiuneUndo {
private:
	Produs p;
	Repo& repo;
public:
	// Constructorul clasei UndoSterge derivate din ActiuneUndo
	// repo - referinta la un repository-ul de fisiere
	// p - produsul sters care prin undo va fi adaugat la loc
	UndoSterge(Repo& repo, const Produs& p) : repo{ repo }, p{ p }{}

	// Functia care face undo suprascrisa pentru UndoSterge
	void doUndo() override {
		repo.add(p);
	}
};

class UndoModifica : public ActiuneUndo {
private:
	Produs p;
	Repo& repo;
public:
	// Constructorul clasei UndoModifica derivate din ActiuneUndo
	// repo - referinta la un repository-ul de fisiere
	// p - produsul initial a carui modificari vor fi restabilite la undo
	UndoModifica(Repo& repo, const Produs& p) : repo{ repo }, p{ p } {}

	// Functia care face undo suprascrisa pentru UndoModifica
	void doUndo() override {
		repo.modifica(p.get_id(), p);
	}
};

