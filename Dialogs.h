#pragma once
#include <QtWidgets/qdialog.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include "ProdusServ.h"

class AddUI:public QDialog
{
private:
	ProdusServ& srv;
	QLineEdit* inName = new QLineEdit;
	QLineEdit* inType = new QLineEdit;
	QLineEdit* inPrice = new QLineEdit;
	QLineEdit* inProducer = new QLineEdit;
	QPushButton* btnAddProduct = new QPushButton{ "Add" };
	QPushButton* btnClose = new QPushButton{ "Close" };

	// Functie de initializare a componentelor GUI
	void initGUICmp();

	// Functie de conectare a semnalelor componentelor GUI
	void connectSignals();

	// Functie de initializare a stadiului initial GUI
	void setInitialGUIState();

	// Functie care calculeaza urmatorul id disponibil pentru produs si il returneaza
	int get_next_id();

	// Functie care adauga un produs
	void add_product();

	// Functie care reseteaza campurile de text
	void reset_text();
public:
	// Constructorul clasei AddUI
	// srv - referinta la service-ul ProdusServ
	AddUI(ProdusServ& srv) noexcept :srv{ srv } {
		initGUICmp();
		connectSignals();
		setInitialGUIState();
	}
};

class ModUI :public QDialog
{
private:
	ProdusServ& srv;
	int id;
	QLineEdit* inName = new QLineEdit;
	QLineEdit* inType = new QLineEdit;
	QLineEdit* inPrice = new QLineEdit;
	QLineEdit* inProducer = new QLineEdit;
	QPushButton* btnModifyProduct = new QPushButton{ "Modify" };
	QPushButton* btnClose = new QPushButton{ "Close" };

	// Functie de initializare a componentelor GUI
	void initGUICmp();

	// Functie de conectare a semnalelor componentelor GUI
	void connectSignals();

	// Functie de initializare a stadiului initial GUI
	void setInitialGUIState();

	// Functie care modifica un produs
	void modify_product();

	// Functie care reseteaza campurile de text
	void reset_text();	
public:
	// Constructorul clasei ModUI
	// srv - referinta la service-ul ProdusServ
	ModUI(ProdusServ& srv) noexcept :srv{ srv }{
		initGUICmp();
		connectSignals();
		setInitialGUIState();
	}

	// Functie seteaza id-ul pentru modificare
	// new_id - numar intreg
	void set_id(int new_id);
};

class InfoUI: public QDialog {
private:
	ProdusServ& srv;
	int id;
	QLineEdit* txtName = new QLineEdit;
	QLineEdit* txtType = new QLineEdit;
	QLineEdit* txtPrice = new QLineEdit;
	QLineEdit* txtProducer = new QLineEdit;

	// Functie de initializare a componentelor GUI
	void initGUICmp();

	// Functie de conectare a semnalelor componentelor GUI
	void connectSignals();

	// Functie de initializare a stadiului initial GUI
	void setInitialGUIState();

public:
	// Constructorul clasei InfoUI
	// srv - referinta la service-ul ProdusServ
	InfoUI(ProdusServ& srv) noexcept :srv{ srv } {
		initGUICmp();
		connectSignals();
		setInitialGUIState();
	}

	// Functie seteaza id-ul pentru modificare
	// new_id - numar intreg
	void set_id(int new_id);

	// Functie seteaza datele campurilor
	void set_fields();
};

