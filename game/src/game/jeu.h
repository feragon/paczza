#pragma once

#include <graph/graphe.h>
#include <board/case.h>
#include <board/chemin.h>

class Jeu {
private:
    Graphe<Case, Chemin> *_graphe;

public:
    Jeu(unsigned short nbMonstres);

    Graphe<Case, Chemin> * getGrapge();
};