#include "CosReadOnlyGUI.h"
#include <QtWidgets/qformlayout.h>

void CosReadOnlyGUI::initGUI() {
	QFormLayout* ly = new QFormLayout;
	ly->addRow("Numar produse in cos:", nrTxt);
	setLayout(ly);
}

void CosReadOnlyGUI::connectSignals() {
	cos.addObserver(this);
}

void CosReadOnlyGUI::setInitialState() {
	this->setWindowTitle("CosReadOnlyGUI");
	nrTxt->setText(QString::number(cos.get_all().size()));
	this->setMinimumSize(400, 300);
}

void CosReadOnlyGUI::update() {
	this->repaint();
	nrTxt->setText(QString::number(cos.get_all().size()));
}
