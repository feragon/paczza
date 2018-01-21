#include "player.h"

Player::Player(Position p) {
    _position = p;
    _deplacements = new Liste<Position>(&_position, nullptr);
}

Position* Player::prochainDeplacement() {
    if(_deplacements->next == nullptr)
        return _deplacements->value;
    else {
        return Liste<Position>::depiler(_deplacements);
    }
}

void Player::ajouterDeplacement(double x, double y) {
    _deplacements = new Liste<Position>(new Position(x,y), _deplacements);
}

void Player::resetDeplacement() {
    while(_deplacements->next != nullptr) {
        Liste<Position>::depiler(_deplacements);
    }
}