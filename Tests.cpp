#include "Tests.h"
#include "Produs.h"
#include "ProdusRepo.h"
#include "ProdusServ.h"
#include "Validator.h"
#include <assert.h>
#include <iostream>
#include "TemplateVector.h"
#include "Iterator.h"
#include <fstream>
using namespace std;

void Tests::teste_domeniu() {
	Produs p{ 0,"Lapte","Lactate",2,"SRL" };
	assert(p.get_id()==0);
	assert(p.get_nume() == "Lapte");
	assert(p.get_tip() == "Lactate");
	assert(p.get_pret() == 2);
	assert(p.get_prod() == "SRL");
	p.set_nume("Laptop");
	p.set_tip("Electronice");
	p.set_pret(2000);
	p.set_prod("ASUS");
	assert(p.get_nume() == "Laptop");
	assert(p.get_tip() == "Electronice");
	assert(p.get_pret() == 2000);
	assert(p.get_prod() == "ASUS");

}

void Tests::teste_repo() {
	ProdusRepo repo;
	Produs p{ 0,"Lapte","Lactate",2,"SRL" };
	repo.add(p);
	auto& produse = repo.get_all();
	assert(produse.size() == 1);
	try {
		repo.add(p);}
	catch (RepoException& e) {
		assert(e.get_msg() == "Produs existent deja!\n");
	}
	auto produs = repo.cauta(0);
	assert(produs.get_nume()=="Lapte");
	try {
		produs = repo.cauta(1);}
	catch (RepoException& e) {
		assert(e.get_msg() == "Produs inexistent!\n");
	}
	try {
		repo.modifica(0, p);}
	catch (RepoException& e) {
		assert(e.get_msg() == "Produs existent deja!\n");
	}
	Produs p2{ 0,"Laptop","Electronice",2000,"Asus" };
	repo.modifica(0, p2);
	p = repo.cauta(0);
	assert(p.get_nume() == "Laptop");
	assert(p.get_tip() == "Electronice");
	assert(p.get_pret() == 2000);
	assert(p.get_prod() == "Asus");
	Produs p3{ 1,"Laptop","Electronice",3000,"Asus" };
	try {
		repo.modifica(1, p3);}
	catch (RepoException& e) {
		assert(e.get_msg() == "Produs inexistent!\n");
	}
	repo.add(p3);
	repo.sterge(1);
	assert(produse.size() == 1);
	try {
		repo.sterge(1);}
	catch (RepoException& e) {
		assert(e.get_msg() == "Produs inexistent!\n");
	}
}

void Tests::teste_service() {
	std::ofstream out("text.txt");
	ProdusRepoFile repo("text.txt");
	Cos cos{ repo };
	Validator valid;
	ProdusServ srv{ repo, valid, cos};
	string nume{"Salam"};
	string tip{"Mezeluri"};
	constexpr float pret{10};
	string prod{"Diana"};
	srv.add_produs(0, nume, tip, pret, prod);
	auto produse = srv.get_all();
	assert(produse.at(0).get_nume() == "Salam");
	assert(produse.at(0).get_tip() == "Mezeluri");
	assert(produse.at(0).get_pret() == 10);
	assert(produse.at(0).get_prod() == "Diana");
	assert(produse.size() == 1);
	auto produs = srv.cauta_produs(0);
	assert(produs.get_nume() == "Salam");
	string nume2{ "Carnati" };
	string tip2{ "Carne" };
	constexpr float pret2{ 100 };
	string prod2{ "Diana" };
	srv.modifica_produs(0, nume2, tip2, pret2, prod2);
	produse = srv.get_all();
	assert(produse.at(0).get_nume() == "Carnati");
	assert(produse.at(0).get_tip() == "Carne");
	assert(produse.at(0).get_pret() == 100);
	assert(produse.at(0).get_prod() == "Diana");
	srv.sterge_produs(0);
	produse = srv.get_all();
	assert(produse.size() == 0);
	out.close();
	try {
		ProdusRepoFile repo2("test.txt");}
	catch (RepoException& e) {
		assert(e.get_msg()== "Deschidere a fisierului nereusita!\n");
	}
	srv.undo();
	produse = srv.get_all();
	assert(produse.size() == 1);
	srv.undo();
	produse = srv.get_all();
	assert(produse.at(0).get_nume()=="Salam");
	srv.undo();
	produse = srv.get_all();
	assert(produse.size() == 0);
	try {
		srv.undo();}
	catch (SrvException& e) {
		assert(e.get_msg() == "Nu se mai poate face undo!\n");
	}
}

void Tests::teste_validare() {
	Validator valid;
	Produs p{ 0,"","",-1,"" };
	try {
		valid.valideaza(p); }
	catch (ValidException& e) {
		assert(e.get_msg() == "Nume invalid!\nTip invalid!\nPret invalid!\nProducator invalid!\n");
	}
}

void Tests::teste_filtrare() {
	std::ofstream out("text.txt");
	ProdusRepoFile repo("text.txt");
	Cos cos{ repo };
	Validator valid;
	ProdusServ srv{ repo, valid, cos };
	Produs p{ 0,"Lapte","Lactate",2,"SRL" };
	repo.add(p);
	Produs p1{ 1,"Salam","Mezeluri",10,"Diana" };
	repo.add(p1);
	Produs p2{ 2,"Branza","Lactate",23,"SRL" };
	repo.add(p2);
	auto produse = srv.filtreaza_float(20);
	assert(produse.size() == 2);
	produse = srv.filtreaza_str("2","Salam");
	assert(produse.size() == 1);
	produse = srv.filtreaza_str("3","SRL");
	assert(produse.size() == 2);
	// teste raport 
	const auto& dict = srv.raport();
	assert(dict.find("Lactate") != dict.end());
	assert(dict.at("Lactate").get_tip() == "Lactate");
	assert(dict.at("Lactate").get_count() == 2);
	out.close();
}

void Tests::teste_sortare() {
	std::ofstream out("text.txt");
	ProdusRepoFile repo("text.txt");
	Cos cos{ repo };
	Validator valid;
	ProdusServ srv{ repo, valid, cos };
	const Produs p{ 0,"Lapte","Lactate",2,"SRL" };
	repo.add(p);
	const Produs p1{ 1,"Salam","Mezeluri",10,"Diana" };
	repo.add(p1);
	const Produs p2{ 2,"Branza","Lactate",23,"SRL" };
	repo.add(p2);
	auto produse = srv.sorteaza("1");
	assert(produse.at(0).get_nume() == "Branza");
	assert(produse.at(1).get_nume() == "Lapte");
	assert(produse.at(2).get_nume() == "Salam");
	produse = srv.sorteaza("2");
	assert(produse.at(0).get_pret() == 2);
	assert(produse.at(1).get_pret() == 10);
	assert(produse.at(2).get_pret() == 23);
	const Produs p3{ 3,"Branza","Topita",15,"SRL" };
	repo.add(p3);
	produse = srv.sorteaza("3");
	assert(produse.at(0).get_tip() == "Lactate");
	assert(produse.at(1).get_tip() == "Topita");
	assert(produse.at(2).get_tip() == "Lactate");
	assert(produse.at(3).get_tip() == "Mezeluri");
	const ProdusRepoFile repo2("text.txt");
	out.close();
}


void Tests::teste_vector_din() {
	VectorDin<Produs> vec;
	Produs p{ 0,"1","1",1,"1" };
	vec.push_back(p);
	assert(vec.size() == 1);
	Produs p2{ 1,"2","2",1,"1" };
	vec.push_back(p2);
	assert(vec.size() == 2);
	for (int i = 0; i < vec.size(); i++) {
		const Produs& ok = vec.at(i);
		assert(ok.get_id() == i);
	}
	VectorDin<Produs> v = vec;
	assert(v.size() == 2);
	v = vec;
	assert(v.size() == 2);
	v = v;
	assert(v.size() == 2);
	assert(vec.at(1).get_id() == p2.get_id());
	vec.erase(1);
	assert(vec.size() == 1);
	vec.push_back(p2);
	Iterator<Produs> it = vec.begin();
	assert(it.elem().get_id() == 0);
	it++;
	assert(it.elem().get_id() == 1);
	assert(it.valid() == true);
	Iterator<Produs> it2 = vec.begin();
	for (auto x : vec) {
		it2++;
	}
	it.prim();
	while (it != vec.end()) {
		it++;
	}
	assert(it == vec.end());
	assert(it.valid() == false);
	assert(!(it == vec.begin()));
	vec.erase(0);
	assert(vec.size() == 1);
	try {
		vec.erase(5);}
	catch (VectorException& e) {
		assert(e.get_msg() == "Index invalid!\n");
	}
	try {
		vec.at(5);}
	catch (VectorException& e) {
		assert(e.get_msg() == "Index invalid!\n");
	}
	try {
		it.elem();}
	catch (IteratorException& e) {
		assert(e.get_msg() == "Iterator invalid!\n");
	}
	try {
		it++;}
	catch (IteratorException& e) {
		assert(e.get_msg() == "Iterator invalid!\n");
	}
}

void Tests::teste_cos() {
	std::ofstream out("text.txt");
	ProdusRepoFile repo("text.txt");
	Cos cos{ repo };
	Validator valid;
	ProdusServ srv{ repo, valid, cos };
	Produs p{ 0,"Lapte","Lactate",2,"SRL" };
	repo.add(p);
	Produs p1{ 1,"Salam","Mezeluri",10,"Diana" };
	repo.add(p1);
	Produs p2{ 2,"Branza","Lactate",23,"SRL" };
	repo.add(p2);
	srv.adauga_cos(0);
	assert(srv.get_all_cos().size() == 1);
	assert(srv.total_cos() == 2);
	srv.golire_cos();
	assert(srv.get_all_cos().size() == 0);
	srv.generare_cos(5);
	assert(srv.get_all_cos().size() == 5);
	srv.export_cos("test.csv");
	try {
		srv.export_cos("a");
	}
	catch (CosException& e) {
		assert(e.get_msg() == "Fisier CSV invalid!\n");
	}
	srv.golire_cos();
	srv.adauga_cos(0);
	srv.adauga_cos(0);
	srv.sterge_produs(0);
	assert(srv.get_all_cos().size() == 0);
	srv.adauga_cos(1);
	srv.modifica_produs(1, "boia", "condimente", 5, "Delikat");
	auto cosulet = srv.get_all_cos();
	assert(cosulet.at(0).get_nume() == "boia");
	assert(cosulet.at(0).get_tip() == "condimente");
	assert(cosulet.at(0).get_pret() == 5);
	assert(cosulet.at(0).get_prod() == "Delikat");
	out.close();
}

void Tests::teste_random() {
	Produs p{ 0,"Lapte","Lactate",2,"SRL" };
	Produs p1{ 1,"Salam","Mezeluri",10,"Diana" };
	Produs p2{ 2,"Branza","Lactate",23,"SRL" };
	RepoLab repo2(0);
	repo2.add(p);
	try {
		repo2.add(p);}
	catch (...) {
		assert(true);}
	repo2.get_all();
	repo2.cauta(0);
	try {
		repo2.cauta(1);}
	catch (...) {
		assert(true);}
	try {
		repo2.modifica(0,p);}
	catch (...) {
		assert(true);}
	repo2.modifica(0,p1);
	try {
		repo2.modifica(3,p2);}
	catch (...) {
		assert(true);}
	repo2.sterge(0);
	try {
		repo2.sterge(5);}
	catch (...) {
		assert(true);}
	RepoLab repo3(1);
	try {
		repo3.add(p);}
	catch (...) {
		assert(true);}
}

void Tests::ruleaza_teste() {
	teste_domeniu();
	teste_repo();
	teste_service();
	teste_validare();
	teste_filtrare();
	teste_sortare();
	teste_vector_din();
	teste_cos();
	teste_random();
}