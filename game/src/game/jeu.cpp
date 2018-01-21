#include "jeu.h"

Jeu::Jeu(unsigned short nbMonstres) {
    int i = 13;
    int j = 8;

    Position positionJoueur(3, 5);

    Liste<Position>* positionsReservees = nullptr;
    positionsReservees = new Liste<Position>(&positionJoueur, positionsReservees);

    _plateau = new Board(i, j, positionsReservees);

    _joueur = new Joueur(positionJoueur);
}

Jeu::~Jeu() {
    delete _plateau;
    delete _joueur;
}

Board* Jeu::plateau() {
    return _plateau;
};

Joueur * Jeu::joueur() {
    return _joueur;
}