#include "monstermanager.h"

MonsterManager::MonsterManager(Board* board) {
    _board = board;
}

Position<double> MonsterManager::newPosition(const Monster* monster) const {
    return _newPositions.at(monster);
}