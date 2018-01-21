#pragma once

#include "monstermanager.h"

class DumbMonsterManager : public MonsterManager {
    public:
        DumbMonsterManager(const Board* board);

        void moveMonsters() override;
};