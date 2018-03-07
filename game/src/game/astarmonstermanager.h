#pragma once

#include "monstermanager.h"

class AStarMonsterManager : public MonsterManager {
    public:
        /**
         * @brief Crée un gestionnaire de monstre utilisant A*
         * @param game Jeu
         */
        AStarMonsterManager(Jeu* game);

        void moveMonster(const Monster* monster, const Position<>& playerPosition) override;
};