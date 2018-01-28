#include "monster.h"

Monster::Monster(const Sommet<Case>* p, Direction direction) :
        Player(p, direction) {
    _isWeak = false;
}
