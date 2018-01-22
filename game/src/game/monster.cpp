#include "monster.h"

Monster::Monster(const Position<double>& p) :
        Player(p) {
    _isWeak = false;
}
