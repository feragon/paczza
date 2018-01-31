#pragma once

#include "monstermanager.h"

class AStarMonsterManager : public MonsterManager {
    public:
        AStarMonsterManager(Board* board);

        void moveMonsters(const Position<>& playerPosition) override;
};