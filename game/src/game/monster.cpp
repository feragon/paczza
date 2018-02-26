#include "monster.h"
#include "pacmandied.h"
#include <board/case.h>

Monster::Monster(const Sommet<Case>* p, Direction direction, Sommet<Case>* home) :
        Player(p, direction),
        _home(home) {
    _isWeak = false;
    _returnHome = false;
}

void Monster::collision(Pacman& pacman) {
    if(_isWeak) {
        if(!_returnHome) {
            pacman.addPoints(200);
            _returnHome = true;
        }
    }
    else {
        throw PacmanDied("Le joueur est mort");
    }
}

std::string Monster::toString() const {
    std::ostringstream oss;
    oss << "Monster(" << Player::toString() << "; " <<
           "_isWeak=" << _isWeak << "; " <<
           "_returnHome=" << _returnHome << "; "
           "_home=" << _home << ")";
    return oss.str();
}
