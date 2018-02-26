#include "pacmangame.h"
#include "dumbmonstermanager.h"
#include "sensemonstermanager.h"
#include "astarmonstermanager.h"
#include "nomorelevels.h"

PacmanGame::PacmanGame() : Jeu() {
    _levels.push_back(SharedPtr<DumbMonsterManager>(plateau()));
    _levels.push_back(SharedPtr<SenseMonsterManager>(plateau()));
    _levels.push_back(SharedPtr<AStarMonsterManager>(plateau()));

    _level = 1;
    setMonsterManager(_levels[0]);
}

void PacmanGame::start() {
    if(remainingPoints() == 0) {
        changeLevel();
    }
    Jeu::start();
}

void PacmanGame::changeLevel() {
    _level++;
    if(_level > _levels.size()) {
        throw NoMoreLevels();
    }

    setMonsterManager(_levels[_level - 1]);
    plateau()->placeElements();
    updatePoints();
    plateau()->player().addLife(2);
}