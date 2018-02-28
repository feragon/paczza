#include "player.h"
#include <board/case.h>

Player::Player(const Sommet<Case<Element>>* p, Direction direction) {
    _position = p;
    _direction = direction;
    _avancement = 0;
}

std::string Player::toString() const {
    std::ostringstream oss;
    oss << "Player(_position=" << (*_position) << "; "
        << "_direction=" << _direction << "; "
        << "_avancement=" << _avancement << ")";
    return oss.str();
}

Player::operator std::string() {
    return toString();
}

std::ostream& operator<<(std::ostream& o, const Player* player) {
    o << player->toString();
    return o;
}
