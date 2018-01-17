#include "joueur.h"

Joueur::Joueur(Position p) {
    _position = p;
    _points = 0;
}

Position Joueur::position() {
    return _position;
}

void Joueur::setPosition(Position p) {
    _position = p;
}

int Joueur::points() {
    return _points;
}

void Joueur::addPoints(int pts) {
    _points += pts;
}