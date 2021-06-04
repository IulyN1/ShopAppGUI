#include "Cos.h"
#include <fstream>
#include <algorithm>
#include <regex>
#include <random>

string CosException::get_msg() {
	return msg;
}

void Cos::adauga(const Produs& produs) {
	in_cos.push_back(produs);
	notify();
}

void Cos::genereaza(int nr) {
	auto rez = repo.get_all();
	while (nr > 0) {
		std::mt19937 mt{ std::random_device{}() };
		const std::uniform_int_distribution<> dist(0, (int)rez.size() - 1);
		const int rndNr = dist(mt);
		adauga(rez.at(rndNr));
		nr--;
	}
}

const vector<Produs>& Cos::get_all() const noexcept{
	return in_cos;
}

void Cos::goleste() noexcept{
	in_cos.clear();
	notify();
}

float Cos::checkout() noexcept{
	float total{ 0 };
	for (const auto& p : in_cos) {
		total += p.get_pret();
	}
	return total;
}

void Cos::exportCSV(const string& filename) {
	if (std::regex_match(filename, std::regex("(.+).csv"))) {
		std::ofstream out{ filename };
		for (const auto& p : in_cos) {
			out << p.get_nume() << "," << p.get_tip() <<
				"," << p.get_pret() << "," << p.get_prod() << "\n";
		}
		out.close();
	}
	else {
		throw CosException("Fisier CSV invalid!\n");
	}
}

void Cos::modifica(int id, const Produs& p) {
	for (auto& produs : in_cos) {
		if (produs.get_id() == id) {
			produs.set_nume(p.get_nume());
			produs.set_tip(p.get_tip());
			produs.set_pret(p.get_pret());
			produs.set_prod(p.get_prod());
		}
	}
	notify();
}

void Cos::sterge(int id) {
	auto it = std::remove_if(in_cos.begin(), in_cos.end(), [id](const Produs& p) noexcept
		{if (p.get_id() == id)return true;
	return false; });
	in_cos.resize(std::distance(in_cos.begin(), it));
	notify();
}