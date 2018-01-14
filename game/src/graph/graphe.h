#pragma once

#include "elementsommet.h"
#include "elementarete.h"

template<class S, class T>
class Graphe {
private:
    ElementSommet<S> *_listeSommets;
    ElementArete<S,T> *_listeAretes;

public:
    Graphe(int largeur, int hauteur);
};


template <class S, class T>
Graphe<S,T>::Graphe(int largeur, int hauteur) {

    S *s1 = new S(1,1);
    S *s2 = new S(1,2);
    S *s3 = new S(2,1);
    S *s4 = new S(2,2);

    _listeSommets = new ElementSommet<S>(s1, new ElementSommet<S>(s2, new ElementSommet<S>(s3, new ElementSommet<S>(s4, NULL))));

    T *a1 = new T(0);
    T *a2 = new T(3);
    T *a3 = new T(1);

    _listeAretes = new ElementArete<S,T>(a1, s1, s2, new ElementArete<S,T>(a2, s1, s4, new ElementArete<S,T>(a3, s3, s4, NULL)));
}