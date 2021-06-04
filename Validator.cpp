#include "Validator.h"

string ValidException::get_msg() {
	return msg;
}

const void Validator::valideaza(const Produs& p) const{
	string erori{ "" };
	if (p.get_nume() == "") {
		erori += "Nume invalid!\n";
	}
	if (p.get_tip() == "") {
		erori += "Tip invalid!\n";
	}
	if (p.get_pret() <= 0) {
		erori += "Pret invalid!\n";
	}
	if (p.get_prod() == "") {
		erori += "Producator invalid!\n";
	}
	if (erori != "") {
		throw ValidException(erori);
	}
}