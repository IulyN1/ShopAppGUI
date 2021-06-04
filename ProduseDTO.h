#pragma once
#include <string>
using std::string;

class ProduseDTO
{
private:
	string tip;
	int count;
public:
	// Constructorul default al obiectului DTO
	ProduseDTO() :tip{ "" }, count{ 0 }{}

	// Constructor explicit al obiectului DTO
	// tip - string
	// count - numar intreg
	ProduseDTO(const string& tip, int count) : tip{ tip }, count{ count }{}

	// Functie care returneaza tipul
	const string& get_tip() const noexcept{
		return tip;
	}

	// Functie care returneaza numarul de aparitii
	const int get_count() const noexcept{
		return count;
	}

	// Functie care incrementeaza numarul de aparitii
	void increment() noexcept{
		count++;
	}
};

