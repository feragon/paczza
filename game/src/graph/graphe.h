#pragma once

#include <iostream>
#include <vector>
#include "sommet.h"
#include "arete.h"

template<class S, class T>
class Graphe {
private:
    std::vector<Sommet<S>*> _sommets;
    std::vector<Arete<S,T>*> _aretes;
    unsigned int _columns;
    unsigned int _rows;

    void genererGraphe();

public:
    Graphe(unsigned int colonnes, unsigned int lignes);

    unsigned int columns();
    unsigned int rows();

    void afficherListeSommets();
    void afficherListeAretes();

    Sommet<S>* sommet(const Position& position);
    std::vector<Sommet<S>*> sommetsIncidents(Sommet<S>* sommet);

    std::vector<Sommet<S>*> sommets();
    std::vector<Arete<S,T>*> aretes();
};


template <class S, class T>
Graphe<S,T>::Graphe(unsigned int colonnes, unsigned int lignes) {
    _columns = colonnes;
    _rows = lignes;

    genererGraphe();
}

template <class S, class T>
void Graphe<S,T>::genererGraphe() {
    for(int k = (_columns*_rows)-1; k >= 0; k--) {
        _sommets.push_back(new Sommet<S>(Position((k%_columns)+1, (k/_columns)+1), NULL));
    }

    srand(time(NULL)); int nb, alea_x1, alea_y1, alea_x2, alea_y2;

    for(int i = 1; i <= _rows; i++) {
        for(int j = 1; j <= _columns; j++) {

            /* Ca fait un quadrillage :) */

            nb = rand() % 100;
            if (nb < 80)
                if(j < _columns)
                    _aretes.push_back(new Arete<S, T>(NULL, sommet(Position(j, i)), sommet(Position(j + 1, i))));

            nb = rand() % 100;
            if (nb < 55)
                if(i < _rows)
                    _aretes.push_back(new Arete<S, T>(NULL, sommet(Position(j, i)), sommet(Position(j, i + 1))));

        }
    }

    for(int i = 0; i < _columns; i++) {
        //Sommet1 aleatoire
        alea_x1 = rand() % _columns + 1;
        alea_y1 = rand() % _rows + 1;

        //Sommet2 voisin
        alea_x2 = alea_x1 % 3 ? alea_x1 - 1 : alea_x1 + 1;
        alea_y2 = alea_y1 % 3 ? alea_y1 - 1 : alea_y1 + 1;

        //si Sommet1 est sur un bord on force la direction de Sommet2
        if(alea_x1 == 1) alea_x2 = alea_x1+1;
        if(alea_x1 == _columns) alea_x2 = alea_x1-1;
        if(alea_y1 == 1) alea_y2 = alea_y1+1;
        if(alea_y1 == _rows) alea_y2 = alea_y1-1;

        _aretes.push_back(new Arete<S, T>(NULL, sommet(Position(alea_x1, alea_y1)), sommet(Position(alea_x2, alea_y2))));
        std::cout << alea_x1 << ","<< alea_y1 << " / "<< alea_x2 << ","<< alea_y2 << "," << std::endl;
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
    for(Sommet<S>* sommet : _sommets) {
        std::cout << *sommet << std::endl;
    }
};

template <class S, class T>
void Graphe<S,T>::afficherListeAretes() {
    for(Arete<S, T>* arete : _aretes) {
        std::cout << *arete << std::endl;
    }
};

template <class S, class T>
Sommet<S>* Graphe<S,T>::sommet(const Position& position) {

    if(position.x > _columns || position.x < 1 || position.y > _rows || position.y < 1)
        throw std::invalid_argument("Coordonees inexistantes");

    for(Sommet<S>* sommet : _sommets) {
        if(sommet->position() == position) {
            return sommet;
        }
    }

    throw std::runtime_error("Sommet introuvable");
};

template <class S, class T>
std::vector<Sommet<S>*> Graphe<S,T>::sommetsIncidents(Sommet<S>* sommet) {
    std::vector<Sommet<S>*> res;

    for(Arete<S,T>* arete : _aretes) {
        if(arete->sommet1() == sommet) {
            res.push_back(arete->sommet2());
        }
        else if(arete->sommet2() == sommet) {
            res.push_back(arete->sommet1());
        }
    }

    return res;
};


template <class S, class T>
std::vector<Sommet<S>*> Graphe<S,T>::sommets() {
    return _sommets;
};

template <class S, class T>
std::vector<Arete<S,T>*> Graphe<S,T>::aretes() {
    return _aretes;
};