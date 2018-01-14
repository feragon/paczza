#pragma once

#include <graph/graphe.h>
#include <graph/sommet.h>
#include <graph/arete.h>

class Jeu {
private:
    Graphe<Sommet, Arete> *_graphe;

public:
    Jeu(unsigned short nbMonstres);
};