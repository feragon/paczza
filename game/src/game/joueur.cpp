#include "joueur.h"

Joueur::Joueur(Position p) {
    _position = p;
    _points = 0;
    _deplacements = new Liste<Position>(&_position, nullptr);
}

Position Joueur::position() {
    return _position;
}

void Joueur::setPosition(Position p) {
    _position = p;
}

Position* Joueur::prochainDeplacement() {
    if(_deplacements->next == nullptr)
        return _deplacements->value;
    else {
        return Liste<Position>::depiler(_deplacements);
    }
}

void Joueur::ajouterDeplacement(double x, double y) {
    _deplacements = new Liste<Position>(new Position(x,y), _deplacements);
}

void Joueur::resetDeplacement() {
    while(_deplacements->next != nullptr) {
        Liste<Position>::depiler(_deplacements);
    }
}

int Joueur::points() {
    return _points;
}

void Joueur::addPoints(int pts) {
    _points += pts;
}