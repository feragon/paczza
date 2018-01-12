#include <iostream>
#include "graphe.h"

Graphe::Graphe(int largeur, int hauteur) {

    for(int i = 0; i < largeur; i++) {
        for(int j = 0; j < hauteur; j++) {

            insererSommet(i,j);
            std::cout << *_liste_sommets.back() << std::endl;
        }
    }

    insererArete(*_liste_sommets[0], *_liste_sommets[1]);
    insererArete(*_liste_sommets[0], *_liste_sommets[5]);
}

Graphe::~Graphe() {

}

bool Graphe::sontAdjacents(Sommet &u, Sommet &v) {
    std::vector<Arete*>::const_iterator it;

    if(u.incidentes().size() < v.incidentes().size()) {

        for (it = u.incidentes().begin(); it != u.incidentes().end(); it++)
            if(&(*it)->e1() == &v || &(*it)->e2() == &v) return true;
    }
    else {

        for (it = v.incidentes().begin(); it != v.incidentes().end(); it++)
            if(&(*it)->e1() == &u || &(*it)->e2() == &u) return true;
    }

    return false;
}

void Graphe::insererSommet(int x, int y) {
    _liste_sommets.push_back(new Sommet(x,y));
}
void Graphe::insererArete(Sommet &u, Sommet &v) {
    _liste_aretes.push_back(new Arete(u, v));/*
    u.insererAreteAdj(*_liste_aretes.back());
    v.insererAreteAdj(*_liste_aretes.back());*/
}

std::vector<Sommet *> Graphe::sommets() {
    return _liste_sommets;
}

std::vector<Arete *> Graphe::aretes() {
    return _liste_aretes;
}

std::vector<Arete *> Graphe::incidentes(Sommet &s) {
    return s.incidentes();
}
