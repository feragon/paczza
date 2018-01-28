#include "player.h"

Player::Player(const Sommet<Case>* p, Direction direction) {
    _position = p;
    _direction = direction;
}