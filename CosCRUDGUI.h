#pragma once
#include "Cos.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include "Observer.h"
#include <QtWidgets/qslider.h>
#include <QtWidgets/qtableview.h>
#include "TableModel.h"

class CosCRUDGUI : public QWidget, public Observer
{
private:
	Cos& cos;
	//QTableWidget* tabCart = new QTableWidget{ 20,4 };
	QTableView* tabCart = new QTableView;
	QPushButton* btnEmptyCart = new QPushButton{ "Empty cart" };
	QPushButton* btnGenerateCart = new QPushButton{ "Generate cart" };
	QLineEdit* prodNum = new QLineEdit;
	QSlider* slider = new QSlider{ Qt::Horizontal };

	// Functie care adauga produsele in lista de cos putand fi vizibile pe ecran
	// produse - vector de obiecte Produs
	void addProductsToCartList(const vector<Produs>& produse);

	// Functie de initializare a componentelor GUI
	void initGUI();

	// Functie de conectare a semnalelor componentelor GUI
	void connectSignals();

	// Functie de initializare a stadiului initial GUI
	void setInitialState();

	// Functia care semnaleaza modificarea statusului componentei Observer-ului
	void update() override;
public:
	// Constructorul clasei CosCRUDGUI
	// cos - referinta la clasa Cos
	CosCRUDGUI(Cos& cos) :cos{ cos } {
		tabCart->setModel(new MyTableModel{ cos });
		initGUI();
		connectSignals();
		setInitialState();
	}
};

