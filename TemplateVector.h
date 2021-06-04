#pragma once
#include "Iterator.h"
#include <vector>
using std::vector;

class VectorException {
	string msg;

public:
	// Functie de initializare a clasei de exceptii pentru vector dinamic
	// m - string
	VectorException(string m) :msg{ m } {};

	// Functie care returneaza mesajul de eroare in caz de exceptie
	string get_msg() {
		return msg;
	}
};

template <class T>
class Iterator;

template <class T>
class VectorDin {
	friend class Iterator<T>;
private:
	int cp;
	int lung;
	T* elems;

	// Functie care dubleaza capacitatea vectorului dinamic cand se ajunge la capacitatea maxima
	void resize();
public:

	// Functie de initializare a vectorului dinamic
	VectorDin();

	// Functie de copiere a vectorului dinamic cu un vector din STL
	// ot - referinta la un vector din STL
	VectorDin(const vector<T>& ot);

	// Functie de copiere a vectorului dinamic cu alt vector dinamic
	// ot - referinta la un alt vector dinamic
	VectorDin(const VectorDin<T>& ot);

	// Functie care defineste operatorul =
	// ot - referinta la un vector dinamic
	VectorDin<T>& operator=(const VectorDin<T>& ot);

	// Destructor pentru vectorul dinamic
	~VectorDin();

	// Functie de adaugare in vectorul dinamic
	// p - obiect generic T
	void push_back(const T& p);

	// Functie care returneaza elementul de la un anumit index
	// index - numar intreg
	T& at(int index) const;

	// Functie care sterge un element din vectorul dinamic
	// i - numar intreg
	void erase(int i);

	// Functie care returneaza iteratorul pe vector dinamic pozitionat la inceput
	Iterator<T> begin() const;

	// Functie care returneaza iteratorul pe vector dinamic pozitionat la sfarsit
	Iterator<T> end() const;

	// Functie care returneaza numarul de elemente din vector
	int size() const noexcept;
};

template<class T>
inline void VectorDin<T>::resize()
{
	T* aux = new T[cp * 2];
	for (int i = 0; i < lung; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
	cp = cp * 2;
}

template<class T>
inline VectorDin<T>::VectorDin()
{
	this->cp = 1;
	this->lung = 0;
	this->elems = new T[cp];
}

template<class T>
inline VectorDin<T>::VectorDin(const vector<T>& ot)
{
	this->cp = ot.size();
	this->lung = ot.size();
	this->elems = new T[cp];
	for (int i = 0; i < lung; i++) {
		this->elems[i] = ot.at(i);
	}
}

template<class T>
inline VectorDin<T>::VectorDin(const VectorDin<T>& ot)
{
	this->cp = ot.cp;
	this->lung = ot.lung;
	this->elems = new T[cp];
	for (int i = 0; i < lung; i++) {
		this->elems[i] = ot.at(i);
	}
}

template<class T>
inline VectorDin<T>& VectorDin<T>::operator=(const VectorDin<T>& ot)
{
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	this->cp = ot.cp;
	this->lung = ot.lung;
	this->elems = new T[cp];
	for (int i = 0; i < lung; i++) {
		this->elems[i] = ot.at(i);
	}
	return *this;
}

template<class T>
inline VectorDin<T>::~VectorDin()
{
	delete[] elems;
}

template<class T>
inline void VectorDin<T>::push_back(const T& p)
{
	if (this->lung == this->cp) {
		resize();
	}
	elems[lung++] = p;
}

template<class T>
inline T& VectorDin<T>::at(int index) const
{
	if(index >= 0 && index < lung) {
		return elems[index];
	}
	throw VectorException("Index invalid!\n");
}

template<class T>
inline void VectorDin<T>::erase(int index)
{
	if (index < 0 || index >= lung) {
		throw VectorException("Index invalid!\n");
	}
	for (int i= index; i < lung-1; i++) {
		elems[i] = elems[i + 1];
	}
	this->lung--;
}

template<class T>
inline Iterator<T> VectorDin<T>::begin() const
{
	return Iterator<T>(*this);
}

template<class T>
inline Iterator<T> VectorDin<T>::end() const
{
	return Iterator<T>(*this,lung);
}

template<class T>
inline int VectorDin<T>::size() const noexcept
{
	return this->lung;
}
