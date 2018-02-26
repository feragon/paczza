#include "monster.h"
#include <board/case.h>

Monster::Monster(const Sommet<Case>* p, Direction direction, Sommet<Case>* home) :
        Player(p, direction),
        _home(home) {
    _isWeak = false;
    _returnHome = false;
}

std::string Monster::toString() const {
    std::ostringstream oss;
    oss << "Monster(" << Player::toString() << "; " <<
           "_isWeak=" << _isWeak << "; " <<
           "_returnHome=" << _returnHome << "; "
           "_home=" << _home << ")";
    return oss.str();
}
