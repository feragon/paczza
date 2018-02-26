#pragma once

#include "monstermanager.h"

class AStarMonsterManager : public MonsterManager {
    public:
        AStarMonsterManager(Jeu* game);

        void moveMonster(const Monster* monster, const Position<>& playerPosition) override;
};