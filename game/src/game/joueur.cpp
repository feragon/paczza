#include "joueur.h"

Joueur::Joueur(Position p) {
    _position = p;
}

Position Joueur::position() {
    return _position;
}

void Joueur::setPosition(Position p) {
    _position = p;
}