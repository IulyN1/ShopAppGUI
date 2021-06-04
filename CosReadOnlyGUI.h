#pragma once
#include "Cos.h"
#include <QtWidgets/qwidget.h>
#include "Observer.h"
#include <QtWidgets/qlabel.h>
#include <qpainter.h>

class CosReadOnlyGUI: public QWidget, public Observer
{
private:
	Cos& cos;
	QLabel* nrTxt = new QLabel;

	// Functie de initializare a componentelor GUI
	void initGUI();

	// Functie de conectare a semnalelor componentelor GUI
	void connectSignals();

	// Functie de initializare a stadiului initial GUI
	void setInitialState();

	// Functia care semnaleaza modificarea statusului componentei Observer-ului
	void update() override;
public:
	// Constructorul clasei CosReadOnlyGUI
	// cos - referinta la clasa Cos
	CosReadOnlyGUI(Cos& cos) :cos{ cos } {
		initGUI();
		connectSignals();
		setInitialState();
	}

	// Functie care suprascrie evenimentul de paint al ferestrei
	//ev - pointer la QPaintEvent
	void paintEvent(QPaintEvent* ev) override {
		ev = 0;
		QPainter p{ this };
		int nr = (int)cos.get_all().size();
		for (int i = 0; i < nr; i++) {
			int x = rand() % 200 + 50;
			int y = rand() % 200 + 50;
			p.drawRect(x, y, 40, 20);
		}
	}
};