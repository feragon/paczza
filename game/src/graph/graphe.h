#pragma once

#include <iostream>
#include "elementsommet.h"
#include "elementarete.h"

template<class S, class T>
class Graphe {
private:
    ElementSommet<S> *_listeSommets;
    ElementArete<S,T> *_listeAretes;
    unsigned int _largeur;
    unsigned int _hauteur;

    void genererGraphe(unsigned int i, unsigned int j);

public:
    Graphe(unsigned int largeur, unsigned int hauteur);

    unsigned int largeur();
    unsigned int hauteur();

    void afficherListeSommets();
    void afficherListeAretes();

    S * sommet(unsigned int i, unsigned int j);
};


template <class S, class T>
Graphe<S,T>::Graphe(unsigned int largeur, unsigned int hauteur) {

    _largeur = largeur;
    _hauteur = hauteur;

    genererGraphe(largeur, hauteur);

    afficherListeSommets();
    afficherListeAretes();
}

template <class S, class T>
void Graphe<S,T>::genererGraphe(unsigned int i, unsigned int j) {

    _listeSommets = NULL;
    _listeAretes = NULL;

    for(int k = (i*j)-1; k >= 0; k--) {
        S *s = new S((k/i)+1, (k%i)+1);

        _listeSommets = new ElementSommet<S>(s, _listeSommets);
    }

    for(int i = 1; i <= _hauteur; i++) {
        for(int j = 1; j <= _largeur; j++) {

            if(j < _largeur) {

                T *a = new T(0);
                _listeAretes = new ElementArete<S,T>(a, sommet(i, j), sommet(i, j+1), _listeAretes);
            }
        }
    }
};

template <class S, class T>
unsigned int Graphe<S,T>::largeur() {
    return _largeur;
}

template <class S, class T>
unsigned int Graphe<S,T>::hauteur() {
    return _hauteur;
}

template <class S, class T>
void Graphe<S,T>::afficherListeSommets() {

    ElementSommet<S> *temp = _listeSommets;

    while(temp->reste() != NULL) {
        std::cout << *(temp->tete()) << std::endl;
        temp = temp->reste();
    }
    std::cout << *(temp->tete()) << std::endl;
};

template <class S, class T>
void Graphe<S,T>::afficherListeAretes() {

    ElementArete<S,T> *temp = _listeAretes;

    while(temp->reste() != NULL) {
        std::cout << *(temp->tete()) << "{ " << *(temp->sommet1()) << " , " << *(temp->sommet2()) << " }" << std::endl;
        temp = temp->reste();
    }
    std::cout << *(temp->tete()) << "{ " << *(temp->sommet1()) << " , " << *(temp->sommet2()) << " }" << std::endl;
};

template <class S, class T>
S * Graphe<S,T>::sommet(unsigned int i, unsigned int j) {

    if(i > _hauteur || i < 1 || j > _largeur || j < 1)
        throw std::invalid_argument("Coordonees inexistantes");

    unsigned int k = (i-1) * _largeur + (j-1);
    ElementSommet<S> *temp = _listeSommets;

    while(k > 0) {
        temp = temp->reste();
        k--;
    }

    return temp->tete();
};