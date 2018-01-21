#include "jeu.h"

Jeu::Jeu(Liste<Position>* positionMonstres) {
    int i = 13;
    int j = 8;

    Position positionJoueur(3, 5);

    Liste<Position>* positionsReservees = nullptr;
    positionsReservees = new Liste<Position>(&positionJoueur, positionsReservees);

    _plateau = new Board(i, j, positionsReservees);

    _joueur = new Joueur(positionJoueur);

    _monstres = nullptr;
    for(Liste<Position>* monstres = positionMonstres; positionMonstres; positionMonstres = positionMonstres->next) {
        _monstres = new Liste<Joueur>(new Joueur(*(monstres->value)), _monstres);
    }
}

Jeu::~Jeu() {
    delete _plateau;
    delete _joueur;
    Liste<Joueur>::efface2(_monstres);
}

Board* Jeu::plateau() {
    return _plateau;
};

Joueur* Jeu::joueur() {
    return _joueur;
}

Liste<Joueur>* Jeu::monstres() const {
    return _monstres;
}
