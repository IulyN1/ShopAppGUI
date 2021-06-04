#include "ProdusRepo.h"
#include <algorithm>
#include <fstream>
#include <random>

string RepoException::get_msg() {
	return msg;
}

void ProdusRepo::add(const Produs& produs) {
	for (const auto& p : produse) {
		if (p.get_nume() == produs.get_nume() && p.get_tip() == produs.get_tip() && p.get_pret() == produs.get_pret()
			&& p.get_prod() == produs.get_prod()) {
				throw RepoException("Produs existent deja!\n"); } }
	produse.push_back(produs);
}

const vector<Produs> ProdusRepo::get_all() const{
	return produse;
}

const Produs& ProdusRepo::cauta(int id) const{
	auto it = std::find_if(produse.begin(), produse.end(), [id](const Produs& p) {
		if (p.get_id() == id) {
			return true;
		}
		return false;
		});
	if (it != produse.end()) {
		const Produs& product = *it;
		return product;
	}
	throw RepoException("Produs inexistent!\n");}

void ProdusRepo::modifica(int id, const Produs& produs) {
	for (const auto& p : produse) {
		if (p.get_nume() == produs.get_nume() && p.get_tip() == produs.get_tip() && p.get_pret() == produs.get_pret()
			&& p.get_prod() == produs.get_prod()) {
			throw RepoException("Produs existent deja!\n");
		}
	}
	auto it = std::find_if(produse.begin(), produse.end(), [id](const Produs& p){
		if (p.get_id() == id) {
			return true;
		}
		return false;
		});
	if (it != produse.end()) {
		Produs& product = *it;
		product.set_nume(produs.get_nume());
		product.set_tip(produs.get_tip());
		product.set_pret(produs.get_pret());
		product.set_prod(produs.get_prod());
		return;
	}
	throw RepoException("Produs inexistent!\n");}

void ProdusRepo::sterge(int id) {
	auto it = std::find_if(produse.begin(), produse.end(), [id](const Produs& p){
		if (p.get_id() == id) {
			return true;
		}
		return false;
		});
	if (it != produse.end()) {
		produse.erase(it);
		return; }
	throw RepoException("Produs inexistent!\n");}

void ProdusRepoFile::loadFromFile(const string& file) {
	int id{ 0 };
	string nume, tip, producator;
	float pret{ 0 };
	std::ifstream in(file);
	if (!in.is_open()) {
		throw RepoException("Deschidere a fisierului nereusita!\n");
	}
	while (!in.eof()) {
		in >> id;
		if (in.eof())break;
		in >> nume >> tip >> pret >> producator;
		const Produs p{ id, nume, tip, pret, producator };
		ProdusRepo::add(p);
	}
	in.close();
}

void ProdusRepoFile::storeToFile(const string& file) {
	std::ofstream out(file);
	for (const auto& p : get_all()) {
		out << p.get_id() << '\n';
		out << p.get_nume() << '\n';
		out << p.get_tip() << '\n';
		out << p.get_pret() << '\n';
		out << p.get_prod() << '\n';
	}
	out.close();
}

void RepoLab::get_random() const
{
	std::mt19937 mt{ std::random_device{}() };
	const std::uniform_int_distribution<> dist(0, 100);
	const int random_nr = dist(mt);
	const double nr = 100 * prob;
	const int numar_prob = (int)nr;
	if (numar_prob > random_nr)
		throw RepoException("Probabilitatea este mai mare decat numarul generat!\n");}

void RepoLab::add(const Produs& p) {
	get_random();
	for (const auto& produs : dict) {
		if (produs.second.get_nume() == p.get_nume() && produs.second.get_tip() == p.get_tip() &&
			produs.second.get_pret() == p.get_pret() && produs.second.get_prod() == p.get_prod()) {
			throw RepoException("Produs existent deja!\n");}}
	dict[p.get_id()] = p;
}

const vector<Produs> RepoLab::get_all() const{
	get_random();
	vector<Produs> products;
	for (const auto& el : dict) {
		products.push_back(el.second);
	}
	return products;
}
const Produs& RepoLab::cauta(int id) const{
	get_random();
	auto it = dict.find(id);
	if (it != dict.end()) {
		const Produs& el = it->second;
		return el;
	}
	throw RepoException("Produs inexistent!\n");}

void RepoLab::modifica(int id, const Produs & produs) {
	get_random();
	for (const auto& p : dict) {
		if (p.second.get_nume() == produs.get_nume() && p.second.get_tip() == produs.get_tip() && 
			p.second.get_pret() == produs.get_pret() && p.second.get_prod() == produs.get_prod()) {
			throw RepoException("Produs existent deja!\n");}}
	cauta(id);
	Produs& product = dict.at(id);
	product.set_nume(produs.get_nume());
	product.set_tip(produs.get_tip());
	product.set_pret(produs.get_pret());
	product.set_prod(produs.get_prod());
}

void RepoLab::sterge(int id) {
	get_random();
	cauta(id);
	auto it = dict.find(id);
	if (it != dict.end()) {
		dict.erase(it);
		return;}}