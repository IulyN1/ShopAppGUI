#include "CosCRUDGUI.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>

void CosCRUDGUI::initGUI() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	QVBoxLayout* side = new QVBoxLayout;
	QHBoxLayout* gen = new QHBoxLayout;
	lyMain->addWidget(tabCart);
	side->addWidget(btnEmptyCart);
	gen->addWidget(prodNum);
	gen->addWidget(btnGenerateCart);	
	gen->addWidget(slider);
	side->addLayout(gen);
	lyMain->addLayout(side);
	setLayout(lyMain);
}

void CosCRUDGUI::addProductsToCartList(const vector<Produs>& produse) {
	
}

void CosCRUDGUI::connectSignals() {
	cos.addObserver(this);
	QObject::connect(btnEmptyCart, &QPushButton::clicked, this, [=]() {
		cos.goleste();
		addProductsToCartList(cos.get_all());
		});
	QObject::connect(btnGenerateCart, &QPushButton::clicked, this, [=]() {
		auto nr = slider->value();
		if (nr != 0) {
			cos.genereaza(nr);
			addProductsToCartList(cos.get_all());
			return;
		}
		QMessageBox::information(this, "Error", "Please input a positive number!");
		});
	QObject::connect(slider, &QSlider::valueChanged, this, [=](int val) {
		prodNum->setText(QString::number(val));
		});
}

void CosCRUDGUI::setInitialState() {
	addProductsToCartList(cos.get_all());
	prodNum->setMaximumWidth(50);
	this->setWindowTitle("CosCRUDGUI");
	prodNum->setDisabled(true);
}

void CosCRUDGUI::update() {
	addProductsToCartList(cos.get_all());
}