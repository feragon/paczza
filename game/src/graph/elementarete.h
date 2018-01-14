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

    T * tete();
    S * sommet1();
    S * sommet2();
    ElementArete<S,T> * reste();
};


template <class S, class T>
ElementArete<S,T>::ElementArete(T *dataArete, S *sommet1, S *sommet2, ElementArete<S,T> *suivant) {
    this->_dataArete = dataArete;
    this->_sommet1 = sommet1;
    this->_sommet2 = sommet2;
    this->_suivant = suivant;
}

template <class S, class T>
T * ElementArete<S,T>::tete() {
    return _dataArete;
}

template <class S, class T>
S * ElementArete<S,T>::sommet1() {
    return _sommet1;
}

template <class S, class T>
S * ElementArete<S,T>::sommet2() {
    return _sommet2;
}

template <class S, class T>
ElementArete<S,T> * ElementArete<S,T>::reste() {
    return _suivant;
}