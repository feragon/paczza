#pragma once

#include <ostream>

template <class S, class T>
class ElementArete {
private:
    ElementArete<S,T> *_suivant;
    T *_dataArete;
    S *_sommet1;
    S *_sommet2;

public:
    ElementArete(T *dataArete, S *sommet1, S *sommet2, ElementArete<S,T> *suivant);
};


template <class S, class T>
ElementArete<S,T>::ElementArete(T *dataArete, S *sommet1, S *sommet2, ElementArete<S,T> *suivant) {
    this->_dataArete = dataArete;
    this->_sommet1 = sommet1;
    this->_sommet2 = sommet2;
    this->_suivant = suivant;
}