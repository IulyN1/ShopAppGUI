#include "ProdusServ.h"
#include <algorithm>
#include <random>

string SrvException::get_msg() {
	return msg;
}

void ProdusServ::add_produs(int id_produs, const string& nume, const string& tip, float pret, const string& prod) {
	Produs p{ id_produs,nume,tip,pret,prod };
	valid.valideaza(p);
	repo.add(p);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, p));
}

const vector<Produs> ProdusServ::get_all() const{
	const auto& produse = repo.get_all();
	return produse;
}

const Produs& ProdusServ::cauta_produs(int id) const{
	const auto& gasit = repo.cauta(id);
	return gasit;
}

void ProdusServ::modifica_produs(int id, const string& nume, const string& tip, float pret, const string& prod) {
	Produs p{ id,nume,tip,pret,prod };
	valid.valideaza(p);
	const auto produs = cauta_produs(id);
	repo.modifica(id,p);
	cos.modifica(id, p);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, produs));
}

void ProdusServ::sterge_produs(int id) {
	const auto produs = cauta_produs(id);
	repo.sterge(id);
	cos.sterge(id);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, produs));
}

const vector<Produs> ProdusServ::filtreaza_float(float valoare) {
	const auto& produse = repo.get_all();
	vector<Produs> produse_filtr (produse.size());
	auto it = std::copy_if(produse.begin(), produse.end(),produse_filtr.begin(), [valoare](const Produs& p) noexcept
		{if (p.get_pret() <= valoare) { 
			return true; }
		return false; });
	produse_filtr.resize(std::distance(produse_filtr.begin(), it));
	return produse_filtr;
}

const vector<Produs> ProdusServ::filtreaza_str(const string& opt, const string& valoare) {
	const auto& produse = repo.get_all();
	vector<Produs> produse_filtr(produse.size());
	if (opt == "2") {
		auto it = std::copy_if(produse.begin(), produse.end(), produse_filtr.begin(), [valoare](const Produs& p) noexcept
			{if (p.get_nume() == valoare) {
			return true;
		}
		return false; });
		produse_filtr.resize(std::distance(produse_filtr.begin(), it));
	}
	else if (opt == "3") {
		auto it = std::copy_if(produse.begin(), produse.end(), produse_filtr.begin(), [valoare](const Produs& p) noexcept
			{if (p.get_prod() == valoare) {
			return true;
		}
		return false; });
		produse_filtr.resize(std::distance(produse_filtr.begin(), it));
	}
	return produse_filtr;
}

const vector<Produs> ProdusServ::sorteaza(const string& opt) {
	vector<Produs> produse;
	for (const auto& p : repo.get_all()) {
		produse.push_back(p);
	}
	if (opt == "1") {
		std::sort(produse.begin(), produse.end(), [](const Produs& p1, const Produs& p2) noexcept {return p1.get_nume() <
			p2.get_nume(); });
	}
	else if (opt == "2") {
		std::sort(produse.begin(), produse.end(), [](const Produs& p1, const Produs& p2) noexcept {return p1.get_pret() <
			p2.get_pret(); });
	}
	else if (opt == "3") {
		std::sort(produse.begin(), produse.end(), [](const Produs& p1, const Produs& p2) noexcept
			{if (p1.get_nume() == p2.get_nume()) return p1.get_tip() < p2.get_tip(); 
			else return p1.get_nume() < p2.get_nume(); });
	}
	vector<Produs> produse_sort = produse;
	return produse_sort;
}

float ProdusServ::total_cos(){
	const auto total = cos.checkout();
	return total;
}

void ProdusServ::adauga_cos(int id) {
	const auto& produs = cauta_produs(id);
	cos.adauga(produs);
}

const vector<Produs>& ProdusServ::get_all_cos() const{
	const auto& produse_cos = cos.get_all();
	return produse_cos;
}

void ProdusServ::golire_cos(){
	cos.goleste();
}

void ProdusServ::generare_cos(int nr) {
	cos.genereaza(nr);
}

void ProdusServ::export_cos(const string& filename) {
	cos.exportCSV(filename);
}

unordered_map <string, ProduseDTO> ProdusServ::raport() {
	unordered_map <string, ProduseDTO> dict;
	const auto& produse = repo.get_all();
	for (const auto& p : produse) {
		if (dict.find(p.get_tip()) == dict.end()) {
			dict[p.get_tip()] = ProduseDTO(p.get_tip(),1);
		}
		else dict[p.get_tip()].increment();
	}
	return dict;
}

void ProdusServ::undo() {
	if (undoActions.empty()) {
		throw SrvException("Nu se mai poate face undo!\n");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}