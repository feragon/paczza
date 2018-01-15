#include "jeu.h"

Jeu::Jeu(unsigned short nbMonstres) {
    _graphe = new Graphe<Case, Chemin>(8,5);

    _joueur = new Joueur(Position(getGraphe()->columns()/2,getGraphe()->rows()/2));
}

Graphe<Case, Chemin> * Jeu::getGraphe() {
    return _graphe;
};

Joueur * Jeu::getJoueur() {
    return _joueur;
}