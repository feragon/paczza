#include "monster.h"

Monster::Monster(const Position& p) :
        Player(p) {
    _isWeak = false;
}
