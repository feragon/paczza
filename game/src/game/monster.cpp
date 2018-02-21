#include "monster.h"

Monster::Monster(const Sommet<Case>* p, Direction direction) :
        Player(p, direction) {
    _isWeak = false;
}

std::string Monster::toString() const {
    std::ostringstream oss;
    oss << "Monster(" << Player::toString() << "; _isWeak=" << _isWeak << ")";
    return oss.str();
}
