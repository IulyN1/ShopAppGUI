#pragma once
#include "TemplateVector.h"

class IteratorException {
	string msg;

public:
	// Functie de initializare a clasei de exceptii pentru vector iterator
	// m - string
	IteratorException(string m) :msg{ m } {};

	// Functie care returneaza mesajul de eroare in caz de exceptie
	string get_msg() {
		return msg;
	}
};

template <class T>
class VectorDin;

template <class T>
class Iterator {
	friend class VectorDin<T>;
private:
	int index;
	const VectorDin<T>& vec;
public:

	// Constructor al clasei iterator
	// v - referinta la un vector dinamic
	Iterator(const VectorDin<T>& v) noexcept;

	// Constructor al clasei iterator
	// v - referinta la un vector dinamic
	// poz - numar intreg
	Iterator(const VectorDin<T>& v,int poz) noexcept;

	// Functie care defineste operatorul * pentru iterator si returneaza referinta la elementul curent
	T& operator*();

	// Functie care defineste operatorul ++ pentru iterator si returneaza iteratorul
	Iterator<T>& operator++();

	// Functie care defineste operatorul ++ pentru iterator si returneaza iteratorul
	// int - numar intreg
	Iterator<T>& operator++(const int);

	// Functie care defineste operatorul != pentru iterator si returneaza true daca iteratorii refera elemente diferite
	//		si false daca nu
	// it - referinta la un alt Iterator
	bool operator!=(const Iterator& it) noexcept;

	// Functie care defineste operatorul == pentru iterator si returneaza true daca iteratorii refera elemente egale
	//		si false daca nu
	// it - referinta la un alt Iterator
	bool operator==(const Iterator& it);

	// Functie care muta iteratorul la primul element
	void prim();

	// Functie care muta iteratorul la urmatorul element
	void urm();

	// Functie care returneaza elementul curent referit de catre iterator
	T& elem() const;

	// Functie care verifica daca iteratorul este valid
	bool valid() const noexcept;
};

template<class T>
inline Iterator<T>::Iterator(const VectorDin<T>& v) noexcept: vec(v), index{0} {}

template<class T>
inline Iterator<T>::Iterator(const VectorDin<T>& v, int poz) noexcept: vec(v), index{ poz } {}

template<class T>
inline T& Iterator<T>::operator*()
{
	return elem();
}

template<class T>
inline Iterator<T>& Iterator<T>::operator++()
{
	urm();
	return *this;
}

template<class T>
inline Iterator<T>& Iterator<T>::operator++(const int)
{
	urm();
	return *this;
}

template<class T>
inline bool Iterator<T>::operator!=(const Iterator& it) noexcept
{
	if (this->index == it.index) {
		return false;
	}
	return true;
}

template<class T>
inline bool Iterator<T>::operator==(const Iterator& it)
{
	if (this->index != it.index) {
		return false;
	}
	return true;
}

template<class T>
inline void Iterator<T>::prim()
{
	this->index = 0;
}

template<class T>
inline void Iterator<T>::urm()
{
	if (valid()) {
		index++;
		return;
	}
	throw IteratorException("Iterator invalid!\n");}

template<class T>
inline T& Iterator<T>::elem() const
{
	if (valid()) {
		return vec.at(index);
	}
	throw IteratorException("Iterator invalid!\n");}

template<class T>
inline bool Iterator<T>::valid() const noexcept
{
	if (index >= 0 && index < vec.lung) {
		return true;
	}
	return false;
}
