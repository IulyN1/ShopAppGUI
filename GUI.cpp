#include "GUI.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qfiledialog.h>
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"

void GUI::initGUICmp() {
	QHBoxLayout* lyMain = new QHBoxLayout;
	QVBoxLayout* ly = new QVBoxLayout;
	QVBoxLayout* lyBtn = new QVBoxLayout;
	QHBoxLayout* lyFilters = new QHBoxLayout;
	QVBoxLayout* pair1 = new QVBoxLayout;
	QVBoxLayout* pair2 = new QVBoxLayout;
	QVBoxLayout* pair3 = new QVBoxLayout;
	QVBoxLayout* lyRight = new QVBoxLayout;
	QVBoxLayout* lyCart = new QVBoxLayout;
	QHBoxLayout* lyPrice = new QHBoxLayout;
	QHBoxLayout* lyGen = new QHBoxLayout;
	QHBoxLayout* lyCheck = new QHBoxLayout;
	setLayout(lyMain);

	lyMain->addWidget(lstProducts);
	ly->addWidget(tabProducts);	
	lyBtn->addWidget(textSearch);
	lyBtn->addWidget(btnSearch);
	lyBtn->addWidget(btnAdd);
	lyBtn->addWidget(btnModify);
	lyBtn->addWidget(btnDelete);	
	lyBtn->addWidget(btnSortName);
	lyBtn->addWidget(btnSortPrice);
	lyBtn->addWidget(btnSortNameType);	
	lyBtn->addWidget(btnReport);

	pair1->addWidget(textPrice);
	pair1->addWidget(btnFilterPrice);
	lyFilters->addLayout(pair1);
	pair2->addWidget(textName);
	pair2->addWidget(btnFilterName);
	lyFilters->addLayout(pair2);
	pair3->addWidget(textProducer);
	pair3->addWidget(btnFilterProducer);
	lyFilters->addLayout(pair3);
	ly->addLayout(lyFilters);
	ly->addWidget(btnShow);

	lyMain->addLayout(ly);
	lyMain->addStretch();
	lyMain->addLayout(lyBtn);
	lyRight->addWidget(btnUndo);
	lyRight->addWidget(btnCart);
	lyCart->addWidget(tabCart);
	lyPrice->addWidget(price);
	lyPrice->addWidget(totalPrice);
	lyCart->addLayout(lyPrice);
	lyCart->addWidget(btnAddToCart);
	lyCart->addWidget(btnEmptyCart);
	//lyGen->addWidget(prodNum);
	lyGen->addWidget(spin);
	lyGen->addWidget(btnGenerateCart);
	lyCart->addLayout(lyGen);
	lyCart->addWidget(btnExportCart);

	lyCheck->addWidget(check);
	lyCheck->addWidget(setting);
	lyCheck->addStretch();
	lyCart->addLayout(lyCheck);

	lyRight->addLayout(lyCart);
	lyRight->addStretch();
	lyRight->addWidget(btnCosCRUD);
	lyRight->addWidget(btnCosReadOnly);
	lyMain->addStretch();
	lyMain->addLayout(lyRight);
	
}

void GUI::connectSignals() {
	tabCart->setModel(new MyTableModel{ cos });
	tabProducts->setModel(model);
	cos.addObserver(this);
	QObject::connect(btnSortName, &QPushButton::clicked, this, [=]() {
		addProductsToList(srv.sorteaza("1"));
		addProductsToSecondList(srv.sorteaza("1"));
		});
	QObject::connect(btnSortPrice, &QPushButton::clicked, this, [=]() {
		addProductsToList(srv.sorteaza("2"));
		addProductsToSecondList(srv.sorteaza("2"));
		});
	QObject::connect(btnSortNameType, &QPushButton::clicked, this, [=]() {
		addProductsToList(srv.sorteaza("3"));
		addProductsToSecondList(srv.sorteaza("3"));
		});
	QObject::connect(btnDelete, &QPushButton::clicked, this, [=]() {
		delete_product();
		});
	QObject::connect(btnModify, &QPushButton::clicked, this, [=]() {
		modify_product();
		});
	QObject::connect(btnSearch, &QPushButton::clicked, this, [=]() {
		auto val = searchProductsInList(srv.get_all());
		if (val == 0) {
			QMessageBox::information(this, "Information", "No search results found!");
		}
		});
	QObject::connect(btnFilterPrice, &QPushButton::clicked, this, [=]() {
		addProductsToList(srv.filtreaza_float(textPrice->text().toFloat()));
		addProductsToSecondList(srv.filtreaza_float(textPrice->text().toFloat()));
		});
	QObject::connect(btnFilterName, &QPushButton::clicked, this, [=]() {
		addProductsToList(srv.filtreaza_str("2", textName->text().toStdString()));
		addProductsToSecondList(srv.filtreaza_str("2", textName->text().toStdString()));
		});
	QObject::connect(btnFilterProducer, &QPushButton::clicked, this, [=]() {
		addProductsToList(srv.filtreaza_str("3", textProducer->text().toStdString()));
		addProductsToSecondList(srv.filtreaza_str("3", textProducer->text().toStdString()));
		});
	QObject::connect(btnShow, &QPushButton::clicked, this, [=]() {
		addProductsToList(srv.get_all());
		addProductsToSecondList(srv.get_all());
		});
	QObject::connect(btnReport, &QPushButton::clicked, this, [=]() {
		report();
		});
	QObject::connect(btnAdd, &QPushButton::clicked, this, [=]() {
		add_wdgt->setModal(true);
		add_wdgt->exec();
		addProductsToList(srv.get_all());
		addProductsToSecondList(srv.get_all());
		});
	QObject::connect(btnUndo, &QPushButton::clicked, this, [=]() {
		try {
			srv.undo();
		}
		catch (SrvException& se) {
			QMessageBox::information(this, "Error", QString::fromStdString(se.get_msg()));
		}
		addProductsToList(srv.get_all());
		addProductsToSecondList(srv.get_all());
		});
	QObject::connect(btnCart, &QPushButton::toggled, this, [=]() {
		show_cart();
		});
	QObject::connect(btnAddToCart, &QPushButton::clicked, this, [=]() {
		add_cart();
		totalPrice->setText(QString::number(srv.total_cos()));
		});
	QObject::connect(btnEmptyCart, &QPushButton::clicked, this, [=]() {
		srv.golire_cos();
		addProductsToCartList(srv.get_all_cos());
		totalPrice->setText(QString::number(srv.total_cos()));
		});
	QObject::connect(btnGenerateCart, &QPushButton::clicked, this, [=]() {
		auto nr = spin->text().toInt();
		if (nr != 0) {
			srv.generare_cos(nr);
			addProductsToCartList(srv.get_all_cos());
			totalPrice->setText(QString::number(srv.total_cos()));
			return;
		}
		QMessageBox::information(this, "Error", "Please input a positive number!");
		});
	QObject::connect(btnExportCart, &QPushButton::clicked, this, [=]() {
		QString filename;
		if (check->isChecked()) {
			filename = QFileDialog::getSaveFileName(this, "Export cart to CSV", "", "CSV Files (*.csv)");
		}
		else {
			filename = QFileDialog::getSaveFileName(this, "Export cart to CSV");
		}
		try {
			srv.export_cos(filename.toStdString());
		}
		catch (CosException) {
			if (filename != "") {
				QMessageBox::information(this, "Error", "The file is not a CSV file!");
			}
		}
	});
	QObject::connect(lstProducts, &QListWidget::itemSelectionChanged, this, [=]() {
		auto sel = lstProducts->selectedItems();
		if (!sel.isEmpty()) {
			auto id_sel = sel.at(0)->data(Qt::UserRole);
			info_wdgt->set_id(id_sel.toInt());
			info_wdgt->set_fields();
			info_wdgt->setModal(true);
			info_wdgt->exec();
		}
		});
	QObject::connect(btnCosCRUD, &QPushButton::clicked, this, [=]() {
		CosCRUDGUI* new_cos = new CosCRUDGUI{ cos };
		new_cos->show();
		});
	QObject::connect(btnCosReadOnly, &QPushButton::clicked, this, [=]() {
		CosReadOnlyGUI* new_cos = new CosReadOnlyGUI{ cos };
		new_cos->show();
		});
	QObject::connect(tabProducts->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {});
}

void GUI::add_cart() {
	auto sel = tabProducts->selectionModel()->selectedIndexes();
	if (!sel.isEmpty()) {
		auto id_sel = sel.at(0).data(Qt::UserRole);
		srv.adauga_cos(id_sel.toInt());
		addProductsToCartList(srv.get_all_cos());
		return;
	}
	QMessageBox::information(this, "Error", "Please select a product first!");
}

void GUI::show_cart() {
	totalPrice->setText(QString::number(srv.total_cos()));
	if (btnCart->isChecked()) {
		tabCart->show();
		price->show();
		totalPrice->show();
		btnAddToCart->show();
		btnEmptyCart->show();
		btnGenerateCart->show();
		btnExportCart->show();
		//prodNum->show();
		spin->show();
		setting->show();
		check->show();
	}
	else {
		tabCart->hide();
		price->hide();
		totalPrice->hide();
		btnAddToCart->hide();
		btnEmptyCart->hide();
		btnGenerateCart->hide();
		btnExportCart->hide();
		//prodNum->hide();
		spin->hide();
		setting->hide();
		check->hide();
	}
}

void GUI::modify_product() {
	auto sel = tabProducts->selectionModel()->selectedIndexes();
	if (!sel.isEmpty()) {
		auto id_sel = sel.at(0).data(Qt::UserRole);
		mod_wdgt->set_id(id_sel.toInt());
		mod_wdgt->setModal(true);
		mod_wdgt->exec();
		addProductsToList(srv.get_all());
		addProductsToSecondList(srv.get_all());
		return;
	}
	QMessageBox::information(this, "Error", "Please select a product first!");
}

void GUI::delete_product() {
	auto sel = tabProducts->selectionModel()->selectedIndexes();
	if (!sel.isEmpty()) {
		auto id_sel = sel.at(0).data(Qt::UserRole);
		srv.sterge_produs(id_sel.toInt());
		addProductsToList(srv.get_all());
		addProductsToSecondList(srv.get_all());
		return;
	}
	QMessageBox::information(this, "Error", "Please select a product first!");
}

void GUI::report() {
	auto rez = srv.raport();
	QString text = "";
	for (const auto el : rez) {
		text += QString::fromStdString(el.first) + " " + QString::number(el.second.get_count()) + "\n";
	}
	text = text.mid(0, text.size()-1);
	QMessageBox::information(this, "Report", text);
}

void GUI::init_table(QTableWidget* tab) {
	tab->clearSelection();
	tab->clear();
	QStringList headers;
	headers.append("Name");
	headers.append("Type");
	headers.append("Price");
	headers.append("Producer");
	tab->setHorizontalHeaderLabels(headers);
	tab->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void GUI::addProductsToList(const vector<Produs>& produse) {
	model->reset_rows();
	model->setProducts(produse);
}

void GUI::addProductsToCartList(const vector<Produs>& produse) {
	/*
	init_table(tabProducts);
	int i{ 0 };
	for (const auto p : produse) {
		QTableWidgetItem* item1 = new QTableWidgetItem{ QString::fromStdString(p.get_nume()) };
		QTableWidgetItem* item2 = new QTableWidgetItem{ QString::fromStdString(p.get_tip()) };
		QTableWidgetItem* item3 = new QTableWidgetItem{ QString::number(p.get_pret()) };
		QTableWidgetItem* item4 = new QTableWidgetItem{ QString::fromStdString(p.get_prod()) };
		item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
		item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
		item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
		item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
		item1->setData(Qt::UserRole, QString::number(p.get_id()));
		item2->setData(Qt::UserRole, QString::number(p.get_id()));
		item3->setData(Qt::UserRole, QString::number(p.get_id()));
		item4->setData(Qt::UserRole, QString::number(p.get_id()));
		tabProducts->setItem(i, 0, item1);
		tabProducts->setItem(i, 1, item2);
		tabProducts->setItem(i, 2, item3);
		tabProducts->setItem(i, 3, item4);
		i++;
	}
	*/
}

void GUI::addProductsToSecondList(const vector<Produs>& produse) {
	lstProducts->clear();
	for (const auto p : produse) {
		auto text = QString::fromStdString(p.get_nume())+"  "+ QString::fromStdString(p.get_tip())+"  "+
			QString::number(p.get_pret())+"  "+ QString::fromStdString(p.get_prod());
		QListWidgetItem* item = new QListWidgetItem{ text };
		item->setData(Qt::UserRole, QString::number(p.get_id()));
		lstProducts->addItem(item);
	}
}

int GUI::searchProductsInList(const vector<Produs>& produse) {
	int i{ 0 };
	int ok{ 0 };
	addProductsToList(produse);
	addProductsToSecondList(srv.get_all());
	for (const auto p : produse) {
		if (textSearch->text() == QString::fromStdString(p.get_nume())) {
			ok = 1;
			for (int j = 0; j <= 3; j++) {
				model->addRow(i);
			}
			lstProducts->item(i)->setBackground(Qt::yellow);
		}
		i++;
	}
	return ok;
}

void GUI::setInitialGUIState() {
	//init_table(tabProducts);
	tabProducts->setMinimumWidth(450);
	//init_table(tabCart);
	tabCart->setMinimumWidth(300);
	addProductsToList(srv.get_all());
	addProductsToSecondList(srv.get_all());
	this->resize(600, 300);
	this->setWindowTitle("Lidl");
	btnCart->setIcon(QIcon("cart.png"));
	btnCart->setCheckable(true);
	btnCart->setChecked(false);
	show_cart();
	prodNum->setMaximumWidth(50);
	totalPrice->setDisabled(true);
	price->setStyleSheet("QLabel {color:gray;}");
	lstProducts->setStyleSheet("QListWidget::item:selected{background-color:darkgreen;}");
}

void GUI::update() {
	addProductsToCartList(srv.get_all_cos());
	totalPrice->setText(QString::number(srv.total_cos()));
}