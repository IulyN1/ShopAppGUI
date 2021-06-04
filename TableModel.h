#pragma once
#include "Cos.h"
#include <QtWidgets/qtableview.h>
#include "Observer.h"
#include "ProdusServ.h"

class MyTableModel : public QAbstractTableModel, public Observer {
private:
	Cos& cos;
public:
	// Constructorul modelului de tabel pentru cos
	// cos - referinta la obiect Cos
	MyTableModel(Cos& cos) :cos{ cos } {
		cos.addObserver(this);
	}

	// Functie suprascrisa de update
	void update() override {
		emit layoutChanged();
	}

	// Functie suprascrisa care returneaza numarul de randuri
	// parent - QModelIndex
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return cos.get_all().size();
	}

	// Functie suprascrisa care returneaza numarul de coloane
	// parent - QModelIndex
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	// Functie suprascrisa care prelucreaza datele tabelului in functie de rol
	// index - QModelIndex
	// role - intreg
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	// Functie care schimba header-ul tabelului
	// section - intreg
	// orientation - QOrientation
	// role - intreg
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

class MyAdvancedTableModel : public QAbstractTableModel{
private:
	vector<Produs> produse;
	vector<int> rows;
public:
	// Constructorul modelului de tabel pentru produse
	// produse - vector de obiecte Produs
	MyAdvancedTableModel(vector<Produs> produse) :produse{ produse } {
	}

	// Functie suprascrisa care returneaza numarul de randuri
	// parent - QModelIndex
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}

	// Functie suprascrisa care returneaza numarul de coloane
	// parent - QModelIndex
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	// Functie care adauga un rand care urmeaza sa fie colorat la cautare intr-o lista
	// row - intreg
	void addRow(int row) {
		rows.push_back(row);
	}

	// Functie care goleste lista de randuri colorate
	void reset_rows() {
		rows.clear();
	}

	// Functie suprascrisa care prelucreaza datele tabelului in functie de rol
	// index - QModelIndex
	// role - intreg
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	// Functie care schimba header-ul tabelului
	// section - intreg
	// orientation - QOrientation
	// role - intreg
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	// Functie care seteaza produsele in model cand acesta s-a modificat
	// produse - vector de obiecte Produs
	void setProducts(const vector<Produs>& produse);
};

