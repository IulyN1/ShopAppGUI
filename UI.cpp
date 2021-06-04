#include "UI.h"
#include <iostream>
#include <limits>

using std::cin;
using std::cout;

void UI::menu() {
	cout << "1. Afiseaza produse\n2. Adauga produs\n3. Cauta produs\n4. Modifica produs\n5. Sterge produs\n" <<
		"6. Filtrare produse\n7. Sortare produse\n8. Adauga in cos\n9. Afiseaza continut cos\n10. Goleste cos\n"<<
		"11. Genereaza cos\n12. Export cos in CSV\n13. Raport produse dupa tip\n14. Undo\n0. Iesire\n";
}

void UI::afisare_UI() {
	try {
		const auto& produse = srv.get_all();
		if (produse.size() == 0) {
			cout << "Nu exista produse!\n";
		}
		else {
			for (auto& x : produse) {
				cout << "ID: " << x.get_id() << "  Nume: " << x.get_nume() << "  Tip: " << x.get_tip() <<
					"  Pret: " << x.get_pret() << "  Producator: " << x.get_prod() << "\n";
			}
		}
	}
	catch (RepoException& e) {
		cout << e.get_msg();
	}
}

void UI::adauga_UI(int& id) {
	string nume;
	string tip;
	float pret;
	string prod;
	cout << "Nume: ";
	cin >> nume;
	cout << "Tip: ";
	cin >> tip;
	cout << "Pret: ";
	cin >> pret;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	cout << "Producator: ";
	cin >> prod;
	const auto& produse = srv.get_all();
	id = produse.back().get_id()+1;
	try {
		srv.add_produs(id, nume, tip, pret, prod);
		cout << "Produs adaugat!\n";
	}
	catch (RepoException& ex) {
		cout << ex.get_msg();
	}
	catch (ValidException& e) {
		cout << e.get_msg();
	}
}

void UI::cauta_UI() {
	int id_pr;
	cout << "ID: ";
	cin >> id_pr;
	try {
		const auto& gasit = srv.cauta_produs(id_pr);
		cout << "ID: " << gasit.get_id() << "  Nume: " << gasit.get_nume() << "  Tip: " << gasit.get_tip() <<
			"  Pret: " << gasit.get_pret() << "  Producator: " << gasit.get_prod() << "\n";
	}
	catch (RepoException& ex) {
		cout << ex.get_msg();
	}
}

void UI::modifica_UI() {
	int id_pr;
	string nume;
	string tip;
	float pret;
	string prod;
	cout << "ID: ";
	cin >> id_pr;
	cout << "Nume nou: ";
	cin >> nume;
	cout << "Tip nou: ";
	cin >> tip;
	cout << "Pret nou: ";
	cin >> pret;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	cout << "Producator nou: ";
	cin >> prod;
	try {
		srv.modifica_produs(id_pr, nume, tip, pret, prod);
		cout << "Produs modificat!\n";
	}
	catch (RepoException& ex) {
		cout << ex.get_msg();
	}
	catch (ValidException& e) {
		cout << e.get_msg();
	}
}

void UI::sterge_UI() {
	int id_pr;
	cout << "ID: ";
	cin >> id_pr;
	try {
		srv.sterge_produs(id_pr);
		cout << "Produs sters!\n";
	}
	catch (RepoException& ex) {
		cout << ex.get_msg();
	}
}

void UI::filtrare_UI(const string& opt) {
	string nume;
	float pret{0};
	string prod;
	if (opt == "1") {
		cout << "Pret maxim: ";
		cin >> pret;
		const auto& produse = srv.filtreaza_float(pret);
		if (produse.size() == 0) {
			cout << "Nu exista produse!\n";
		}
		else {
			for (auto& x : produse) {
				cout << "ID: " << x.get_id() << "  Nume: " << x.get_nume() << "  Tip: " << x.get_tip() <<
					"  Pret: " << x.get_pret() << "  Producator: " << x.get_prod() << "\n";
			}
		}
	}
	else if (opt == "2") {
		cout << "Nume: ";
		cin >> nume;
		const auto& produse = srv.filtreaza_str(opt, nume);
		if (produse.size() == 0) {
			cout << "Nu exista produse!\n";
		}
		else {
			for (auto& x : produse) {
				cout << "ID: " << x.get_id() << "  Nume: " << x.get_nume() << "  Tip: " << x.get_tip() <<
					"  Pret: " << x.get_pret() << "  Producator: " << x.get_prod() << "\n";
			}
		}
	}
	else if (opt == "3") {
		cout << "Producator: ";
		cin >> prod;
		const auto& produse = srv.filtreaza_str(opt, prod);
		if (produse.size() == 0) {
			cout << "Nu exista produse!\n";
		}
		else {
			for (auto& x : produse) {
				cout << "ID: " << x.get_id() << "  Nume: " << x.get_nume() << "  Tip: " << x.get_tip() <<
					"  Pret: " << x.get_pret() << "  Producator: " << x.get_prod() << "\n";
			}
		}
	}
	else {
		cout << "Optiune invalida!\n";
	}
}

void UI::sortare_UI(const string& opt) {
	if (opt == "1" || opt == "2" || opt == "3") {
		const auto& produse = srv.sorteaza(opt);
		if (produse.size() == 0) {
			cout << "Nu exista produse!\n";
		}
		else {
			for (auto& x : produse) {
				cout << "ID: " << x.get_id() << "  Nume: " << x.get_nume() << "  Tip: " << x.get_tip() <<
					"  Pret: " << x.get_pret() << "  Producator: " << x.get_prod() << "\n";
			}
		}
	}
	else {
		cout << "Optiune invalida!\n";
	}
}

void UI::adauga_cos_UI() {
	int id;
	cout << "Introduceti ID: ";
	cin >> id;
	try {
		srv.adauga_cos(id);
		cout << "Produs adaugat in cos!\n";
		const auto total = srv.total_cos();
		cout << "Pret total: " << total<<'\n';
	}
	catch (RepoException& e) {
		cout << e.get_msg();
	}
}

void UI::afiseaza_cos_UI() {
	const auto& produse = srv.get_all_cos();
	if (produse.size() == 0) {
		cout << "Nu exista produse in cos!\n";
	}
	else {
		cout << "Produse in cos:\n";
		for (auto& x : produse) {
			cout << "  Nume: " << x.get_nume() << "  Tip: " << x.get_tip() <<
				"  Pret: " << x.get_pret() << "  Producator: " << x.get_prod() << "\n";
		}
	}
	const auto total = srv.total_cos();
	cout << "Pret total: " << total << '\n';
}

void UI::goleste_cos_UI() {
	srv.golire_cos();
	cout << "Cosul acum este gol!\n";
	const auto total = srv.total_cos();
	cout << "Pret total: " << total<<'\n';
}

void UI::genereaza_cos_UI() {
	int nr;
	cout << "Introduceti nr de produse dorite: ";
	cin >> nr;
	srv.generare_cos(nr);
	cout << "Cosul a fost generat!\n";
	const auto total = srv.total_cos();
	cout << "Pret total: " << total << '\n';
}

void UI::export_cos_UI() {
	string nume;
	cout << "Introduceti numele fisierului CSV: ";
	cin >> nume;
	try {
		srv.export_cos(nume);
		cout << "Cosul a fost exportat in fisier!\n";
		const auto total = srv.total_cos();
		cout << "Pret total: " << total << '\n';
	}
	catch (CosException& e) {
		cout << e.get_msg();
	}
}

void UI::raport_UI() {
	const auto& dict = srv.raport();
	for (const auto& p : dict) {
		cout << p.second.get_tip() << ' ' << p.second.get_count() << '\n';
	}
}
void UI::undo_UI() {
	try {
		srv.undo();
		cout << "Undo realizat!\n";
	}
	catch (SrvException& e) {
		cout << e.get_msg();
	}
}

void UI::start() {
	menu();
	int id{ 0 };
	string opt;
	while (true) {
		string cmd;
		cout << "Comanda: ";
		cin >> cmd;
		if (cmd == "0") {
			break;
		}
		else if (cmd == "1") {
			afisare_UI();
		}
		else if (cmd == "2") {
			adauga_UI(id);
		}
		else if (cmd == "3") {
			cauta_UI();
		}
		else if (cmd == "4") {
			modifica_UI();
		}
		else if (cmd == "5") {
			sterge_UI();
		}
		else if (cmd == "6") {
			cout << "Optiuni filtrare:\n1. Filtrare dupa pret\n2. Filtrare dupa nume\n3. Filtrare dupa producator\n";
			cout << "Optiune: ";
			cin >> opt;
			filtrare_UI(opt);
		}
		else if (cmd == "7") {
			cout << "Optiuni sortare:\n1. Sortare dupa nume\n2. Sortare dupa pret\n3. Filtrare dupa nume si tip\n";
			cout << "Optiune: ";
			cin >> opt;
			sortare_UI(opt);
		}
		else if (cmd == "8") {
			adauga_cos_UI();
		}
		else if (cmd == "9") {
			afiseaza_cos_UI();
		}
		else if (cmd == "10") {
			goleste_cos_UI();
		}
		else if (cmd == "11") {
			genereaza_cos_UI();
		}
		else if (cmd == "12") {
			export_cos_UI();
		}
		else if (cmd == "13") {
			raport_UI();
		}
		else if (cmd == "14") {
			undo_UI();
		}
		else {
			cout << "Comanda invalida!\n";
		}
	}
	cout << "Bye!";
}