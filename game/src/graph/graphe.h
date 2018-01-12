#pragma once

#include "sommet.h"
#include "arete.h"
#include <iterator>
#include <vector>

class Graphe {
private:
    std::vector<Sommet*> _liste_sommets;
    std::vector<Arete*> _liste_aretes;
    void insererSommet(int x, int y);
    void insererArete(Sommet &u, Sommet &v);
public:
    Graphe(int largeur, int hauteur);
    virtual ~Graphe();

    bool sontAdjacents(Sommet &u, Sommet &v);
    /*
    void modifChaleur(Arete a, int chaleur);
    void enleverSommet(Sommet s);
    void enleverArete(Arete a);
     */
    std::vector<Arete*> incidentes(Sommet &s);
    std::vector<Sommet*> sommets();
    std::vector<Arete*> aretes();
};