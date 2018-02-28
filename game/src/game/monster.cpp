#include "monster.h"
#include "pacmandied.h"
#include <board/case.h>

Monster::Monster(const Sommet<Case<Element>>* p, Direction direction, Sommet<Case<Element>>* home) :
        Player(p, direction),
        _home(home) {
    _weakTime = 0;
    _returnHome = false;
}

void Monster::collision(Pacman& pacman) {
    if(weak()) {
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
           "_weakTime=" << _weakTime << "; " <<
           "_returnHome=" << _returnHome << "; "
           "_home=" << _home << ")";
    return oss.str();
}

void Monster::setWeak(bool isWeak) {
    if(isWeak) {
        _weakTime = WEAK_TIME;
    }
    else {
        _weakTime = 0;
    }
}

bool Monster::update(double timeElapsed) {
    bool changed = false;

    if(_returnHome && position() == _home) {
        _returnHome = false;
        _weakTime = 0;
        changed = true;
    }

    if(_weakTime > 0) {
        _weakTime -= timeElapsed;
        if(_weakTime <= 0) {
            _weakTime = 0;
            changed = !_returnHome;
        }
    }

    return changed;
}
