#include "Dialogs.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>

void AddUI::initGUICmp() {
	QVBoxLayout* mly = new QVBoxLayout;
	QFormLayout* fly = new QFormLayout;
	QHBoxLayout* bly = new QHBoxLayout;
	fly->addRow("Name:", inName);
	fly->addRow("Type:", inType);
	fly->addRow("Price:", inPrice);
	fly->addRow("Producer:", inProducer);
	mly->addLayout(fly);
	bly->addWidget(btnAddProduct);
	bly->addWidget(btnClose);
	mly->addLayout(bly);
	setLayout(mly);
}

void AddUI::connectSignals() {
	QObject::connect(btnAddProduct, &QPushButton::clicked, this, [=]() {
		add_product();
		});
	QObject::connect(btnClose, &QPushButton::clicked, this, [=]() {
		reset_text();
		close();
		});
}

void AddUI::reset_text() {
	inName->setText("");
	inType->setText("");
	inPrice->setText("");
	inProducer->setText("");
}

int AddUI::get_next_id() {
	int mx = 0;
	for (const auto el : srv.get_all()) {
		if (mx < el.get_id()) {
			mx = el.get_id();
		}
	}
	return mx;
}

void AddUI::add_product() {
	auto name = inName->text();
	auto type = inType->text();
	auto price = inPrice->text();
	auto producer = inProducer->text();
	int id = get_next_id();
	try {
		srv.add_produs(++id, name.toStdString(), type.toStdString(),price.toFloat(), producer.toStdString());
		close();
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Error", QString::fromStdString(re.get_msg()));
	}
	catch (ValidException& ve) {
		QMessageBox::information(this, "Error", QString::fromStdString(ve.get_msg()));
	}
	reset_text();
}

void AddUI::setInitialGUIState() {
	this->setWindowTitle("Add product");
}


void ModUI::initGUICmp() {
	QVBoxLayout* mly = new QVBoxLayout;
	QFormLayout* fly = new QFormLayout;
	QHBoxLayout* bly = new QHBoxLayout;
	fly->addRow("New name:", inName);
	fly->addRow("New type:", inType);
	fly->addRow("New price:", inPrice);
	fly->addRow("New producer:", inProducer);
	mly->addLayout(fly);
	bly->addWidget(btnModifyProduct);
	bly->addWidget(btnClose);
	mly->addLayout(bly);
	setLayout(mly);
}

void ModUI::connectSignals() {
	QObject::connect(btnModifyProduct, &QPushButton::clicked, this, [=]() {
		modify_product();
		});
	QObject::connect(btnClose, &QPushButton::clicked, this, [=]() {
		reset_text();
		close();
		});
}

void ModUI::reset_text() {
	inName->setText("");
	inType->setText("");
	inPrice->setText("");
	inProducer->setText("");
}

void ModUI::modify_product() {
	auto name = inName->text();
	auto type = inType->text();
	auto price = inPrice->text();
	auto producer = inProducer->text();
	try {
		srv.modifica_produs(id, name.toStdString(), type.toStdString(), price.toFloat(), producer.toStdString());
		close();
	}
	catch (RepoException& re) {
		QMessageBox::information(this, "Error", QString::fromStdString(re.get_msg()));
	}
	catch (ValidException& ve) {
		QMessageBox::information(this, "Error", QString::fromStdString(ve.get_msg()));
	}
	reset_text();
}

void ModUI::set_id(int new_id) {
	this->id = new_id;
}

void ModUI::setInitialGUIState() {
	this->setWindowTitle("Modify product");
}


void InfoUI::initGUICmp() {
	QFormLayout* ly = new QFormLayout;
	ly->addRow("Name:", txtName);
	ly->addRow("Type:", txtType);
	ly->addRow("Price:", txtPrice);
	ly->addRow("Producer:", txtProducer);
	setLayout(ly);
}

void InfoUI::connectSignals() {

}

void InfoUI::set_fields() {
	try {
		auto p = srv.cauta_produs(id);
		txtName->setText(QString::fromStdString(p.get_nume()));
		txtType->setText(QString::fromStdString(p.get_tip()));
		txtPrice->setText(QString::number(p.get_pret()));
		txtProducer->setText(QString::fromStdString(p.get_prod()));
	}
	catch (...) {};
}

void InfoUI::setInitialGUIState() {
	this->setWindowTitle("Information");
	txtName->setDisabled(true);
	txtType->setDisabled(true);
	txtPrice->setDisabled(true);
	txtProducer->setDisabled(true);
}

void InfoUI::set_id(int new_id) {
	this->id = new_id;
}