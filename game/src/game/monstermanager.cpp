#include "monstermanager.h"

MonsterManager::MonsterManager(const Board* board) {
    _board = board;
}

void MonsterManager::addMonster(const Monster* monster) {
    _newPositions[monster] = monster->position();
}

Position<double> MonsterManager::newPosition(const Monster* monster) const {
    return _newPositions.at(monster);
}

void MonsterManager::removeMonster(const Monster* monster) {
    _newPositions.erase(monster);
}

void MonsterManager::reset() {
    for(std::pair<const Monster* const, Position<double>> pair : _newPositions) {
        _newPositions[pair.first] = pair.first->position();
    }
}
