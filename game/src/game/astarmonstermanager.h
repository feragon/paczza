#pragma once

#include "monstermanager.h"

class AStarMonsterManager : public MonsterManager {
    public:
        AStarMonsterManager(Jeu* game);

        void moveMonsters(const Position<>& playerPosition) override;
};