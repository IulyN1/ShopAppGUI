#include "Produs.h"

int Produs::get_id() const noexcept{
	return id_produs;
}
const string& Produs::get_nume() const noexcept {
	return nume;
}
const string& Produs::get_tip() const noexcept {
	return tip;
}
float Produs::get_pret() const noexcept {
	return pret;
}
const string& Produs::get_prod() const noexcept {
	return prod;
}
void Produs::set_nume(const string& name){
	nume = name;
}
void Produs::set_tip(const string& type) {
	tip = type;
}
void Produs::set_pret(float price) noexcept{
	pret = price;
}
void Produs::set_prod(const string& produc) {
	prod = produc;
}