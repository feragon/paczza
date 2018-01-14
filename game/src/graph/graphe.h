#pragma once

#include <iostream>
#include "elementsommet.h"
#include "elementarete.h"

template<class S, class T>
class Graphe {
private:
    ElementSommet<S> *_listeSommets;
    ElementArete<S,T> *_listeAretes;
    unsigned int _columns;
    unsigned int _rows;

    void genererGraphe();

public:
    Graphe(unsigned int colonnes, unsigned int lignes);

    unsigned int columns();
    unsigned int rows();

    void afficherListeSommets();
    void afficherListeAretes();

    S * sommet(unsigned int colonne, unsigned int ligne);
    ElementSommet<S> * sommetsIncidents(S *sommet);
};


template <class S, class T>
Graphe<S,T>::Graphe(unsigned int colonnes, unsigned int lignes) {

    _columns = colonnes;
    _rows = lignes;

    genererGraphe();

    std::cout << std::endl << "== Generation du graphe :" << std::endl;
    afficherListeSommets();
    afficherListeAretes();

    std::cout << std::endl << "== Sommets incidents à S[3][2] :" << std::endl;
    sommetsIncidents(sommet(3,2));
}

template <class S, class T>
void Graphe<S,T>::genererGraphe() {

    _listeSommets = NULL;
    _listeAretes = NULL;

    for(int k = (_columns*_rows)-1; k >= 0; k--) {
        S *s = new S((k%_columns)+1, (k/_columns)+1);

        _listeSommets = new ElementSommet<S>(s, _listeSommets);
    }

    for(int i = 1; i <= _rows; i++) {
        for(int j = 1; j <= _columns; j++) {

            /* Ca fait un quadrillage :) */

            if(j < _columns) {
                T *a = new T(0);
                _listeAretes = new ElementArete<S,T>(a, sommet(j, i), sommet(j+1, i), _listeAretes);
            }
            if(i < _rows) {
                T *a = new T(0);
                _listeAretes = new ElementArete<S,T>(a, sommet(j, i), sommet(j, i+1), _listeAretes);
            }
        }
    }
};

template <class S, class T>
unsigned int Graphe<S,T>::columns() {
    return _columns;
}

template <class S, class T>
unsigned int Graphe<S,T>::rows() {
    return _rows;
}

template <class S, class T>
void Graphe<S,T>::afficherListeSommets() {

    ElementSommet<S> *temp = _listeSommets;

    while(temp != NULL) {
        std::cout << *(temp->tete()) << std::endl;
        temp = temp->reste();
    }
};

template <class S, class T>
void Graphe<S,T>::afficherListeAretes() {

    ElementArete<S,T> *temp = _listeAretes;

    while(temp != NULL) {
        std::cout << *(temp->tete()) << "{ " << *(temp->sommet1()) << " , " << *(temp->sommet2()) << " }" << std::endl;
        temp = temp->reste();
    }
};

template <class S, class T>
S * Graphe<S,T>::sommet(unsigned int colonne, unsigned int ligne) {

    if(colonne > _columns || colonne < 1 || ligne > _rows || ligne < 1)
        throw std::invalid_argument("Coordonees inexistantes");

    unsigned int k = (ligne-1) * _columns + (colonne-1);
    ElementSommet<S> *temp = _listeSommets;

    while(k > 0) {
        temp = temp->reste();
        k--;
    }

    return temp->tete();
};

template <class S, class T>
ElementSommet<S> * Graphe<S,T>::sommetsIncidents(S *sommet) {

    ElementArete<S,T> *temp = _listeAretes;
    ElementSommet<S> *res = NULL;

    while(temp != NULL) {

        if(temp->sommet1() == sommet) {
            res = new ElementSommet<S>(temp->sommet2(), res);

            std::cout << *(res->tete()) << std::endl;
        }
        else if(temp->sommet2() == sommet) {
            res = new ElementSommet<S>(temp->sommet1(), res);

            std::cout << *(res->tete()) << std::endl;
        }

        temp = temp->reste();
    }

    return res;
};