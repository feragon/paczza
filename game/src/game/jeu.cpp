#include "jeu.h"

Jeu::Jeu(unsigned short nbMonstres) {
    _graphe = new Graphe<Case, Chemin>(5,3);

}

Graphe<Case, Chemin> * Jeu::getGrapge() {
    return _graphe;
};