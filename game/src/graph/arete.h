#pragma once

#include <ostream>

template <class S, class T>
class Arete {
    private:
        T* _dataArete;
        Sommet<S>* _sommet1;
        Sommet<S>* _sommet2;
    
    public:
        Arete(T* dataArete, Sommet<S>* sommet1, Sommet<S>* sommet2);
    
        T* tete();
        Sommet<S>* sommet1();
        Sommet<S>* sommet2();

        template <class osS, class osT>
        friend std::ostream& operator<<(std::ostream& os, const Arete<osS, osT>& arete);
};


template <class S, class T>
Arete<S,T>::Arete(T *dataArete, Sommet<S>* sommet1, Sommet<S>* sommet2) {
    this->_dataArete = dataArete;
    this->_sommet1 = sommet1;
    this->_sommet2 = sommet2;

    _sommet1->setDegre(_sommet1->degre() + 1);
    _sommet2->setDegre(_sommet2->degre() + 1);
}

template <class S, class T>
T * Arete<S,T>::tete() {
    return _dataArete;
}

template <class S, class T>
Sommet<S>* Arete<S,T>::sommet1() {
    return _sommet1;
}

template <class S, class T>
Sommet<S>* Arete<S,T>::sommet2() {
    return _sommet2;
}

template <class S, class T>
std::ostream& operator<<(std::ostream& os, const Arete<S,T>& arete) {
    os << "Arete(_dataArete: " << arete._dataArete <<
               " _sommet1: " << arete._sommet1 <<
               " _sommet2: " << arete._sommet2 <<
    ")";
    return os;
}
