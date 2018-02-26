#include "monstermanager.h"
#include "jeu.h"

MonsterManager::MonsterManager(Jeu* game) {
    _game = game;
}

Position<double> MonsterManager::newPosition(const Monster* monster) const {
    return _newPositions.at(monster);
}