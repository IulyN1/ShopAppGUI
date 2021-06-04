#pragma once
#include "ProdusServ.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qlineedit.h>
#include "Dialogs.h"
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qcheckbox.h>
#include "Observer.h"
#include "Cos.h"
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qtableview.h>
#include "TableModel.h"

class GUI : public QWidget, public Observer
{
private:
	ProdusServ& srv;
	Cos& cos;
	AddUI* add_wdgt = new AddUI{ srv };
	ModUI* mod_wdgt = new ModUI{ srv };
	InfoUI* info_wdgt = new InfoUI{ srv };
	QPushButton* btnCart = new QPushButton{ "" };
	QPushButton* btnUndo = new QPushButton{ "Undo" };
	QPushButton* btnShow = new QPushButton{ "Show products" };
	QPushButton* btnReport = new QPushButton{ "Products report" };
	QPushButton* btnAdd = new QPushButton{ "Add product" };
	QPushButton* btnModify = new QPushButton{ "Modify product" };
	QPushButton* btnDelete = new QPushButton{ "Delete product" };
	QPushButton* btnSearch = new QPushButton{ "Search product" };
	QPushButton* btnFilterPrice = new QPushButton{ "Filter by price" };
	QPushButton* btnFilterName = new QPushButton{ "Filter by name" };
	QPushButton* btnFilterProducer = new QPushButton{ "Filter by producer" };
	QPushButton* btnSortName = new QPushButton{ "Sort by name" };
	QPushButton* btnSortPrice = new QPushButton{ "Sort by price" };
	QPushButton* btnSortNameType = new QPushButton{ "Sort by name and type" };
	QLineEdit* textSearch = new QLineEdit;
	QLineEdit* textPrice = new QLineEdit;
	QLineEdit* textName = new QLineEdit;
	QLineEdit* textProducer = new QLineEdit;

	//QTableWidget* tabProducts = new QTableWidget{ 20,4 };
	QTableView* tabProducts = new QTableView;
	MyAdvancedTableModel* model = new MyAdvancedTableModel{ srv.get_all() };
	//QTableWidget* tabCart = new QTableWidget{ 20,4 };
	QTableView* tabCart = new QTableView;

	QListWidget* lstProducts = new QListWidget;
	QPushButton* btnAddToCart = new QPushButton{ "Add to cart" };
	QPushButton* btnEmptyCart = new QPushButton{ "Empty cart" };
	QPushButton* btnGenerateCart = new QPushButton{ "Generate cart" };
	QPushButton* btnExportCart = new QPushButton{ "Export cart" };
	QLineEdit* totalPrice = new QLineEdit;
	QLabel* price = new QLabel{ "Total price:" };
	QLineEdit* prodNum = new QLineEdit;
	QCheckBox* check = new QCheckBox;
	QLabel* setting = new QLabel{ "Default export type" };
	QPushButton* btnCosCRUD = new QPushButton{ "CosCRUDGUI" };
	QPushButton* btnCosReadOnly = new QPushButton{ "CosReadOnlyGUI" };
	QSpinBox* spin = new QSpinBox;

	// Functie de initializare a componentelor GUI
	void initGUICmp();

	// Functie de conectare a semnalelor componentelor GUI
	void connectSignals();

	// Functie de initializare a stadiului initial GUI
	void setInitialGUIState();

	// Functie care afiseaza sau ascunde cosul de cumparaturi in functie de statusul butonului reprezentativ
	void show_cart();

	// Functie care adauga produs in cos.
	void add_cart();

	// Functie care adauga produsele in lista(table) putand fi vizibile pe ecran
	// produse - vector de obiecte Produs
	void addProductsToList(const vector<Produs>& produse);

	// Functie care adauga produsele in lista de cos putand fi vizibile pe ecran
	// produse - vector de obiecte Produs
	void addProductsToCartList(const vector<Produs>& produse);

	// Functie care adauga produsele in lista(list) putand fi vizibile pe ecran
	// produse - vector de obiecte Produs
	void addProductsToSecondList(const vector<Produs>& produse);

	// Functie de initializare a tabelului
	// tab - pointer la un tabel QWidget
	void init_table(QTableWidget* tab);

	// Functie de cautare a unui produs in tabel
	// produse - vector de obiecte Produs
	int searchProductsInList(const vector<Produs>& produse);

	// Functie care creeaza un raport
	void report();

	// Functie care sterge un produs
	void delete_product();

	// Functie care modifica un produs
	void modify_product();

	// Functia care semnaleaza modificarea statusului componentei Observer-ului
	void update() override;
public:
	// Constructorul clasei GUI
	// srv - referinta la service-ul ProdusServ
	// cos - referinta la clasa Cos
	GUI(ProdusServ& srv, Cos& cos) noexcept : srv{ srv }, cos{ cos } {
		initGUICmp();
		connectSignals();
		setInitialGUIState();
	}
};
