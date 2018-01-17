#pragma once

#include <graph/graphe.h>
#include <board/case.h>
#include <board/chemin.h>
#include <sprite.h>
#include "joueur.h"

class Jeu {
private:
    Graphe<Case, Chemin> *_graphe;
    Joueur *_joueur;

public:
    Jeu(unsigned short nbMonstres);

    Graphe<Case, Chemin> * getGraphe();
    Joueur * getJoueur();

    std::vector<std::pair<Position,Sprite>> _aliments;
};