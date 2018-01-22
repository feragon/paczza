#include "player.h"

Player::Player(Position<double> p) {
    _position = p;
    _deplacements = new Liste<Position<double>>(&_position, nullptr);
}

Position<double>* Player::prochainDeplacement() {
    if(_deplacements->next == nullptr)
        return _deplacements->value;
    else {
        return Liste<Position<double>>::depiler(_deplacements);
    }
}

void Player::ajouterDeplacement(double x, double y) {
    _deplacements = new Liste<Position<double>>(new Position<double>(x,y), _deplacements);
}

void Player::resetDeplacement() {
    while(_deplacements->next != nullptr) {
        Liste<Position<double>>::depiler(_deplacements);
    }
}