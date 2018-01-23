#pragma once

#include "monstermanager.h"

class DumbMonsterManager : public MonsterManager {
    public:
        DumbMonsterManager(const Board* board);

        void moveMonsters(const Position<>& playerPosition) override;

        /**
         * @brief Donne une position aléatoire à côté du sommet actuel
         * @param board Plateau
         * @param monsterVertice Sommet actuel
         * @return Nouvelle position
         */
        static Position<> getNextPosition(const Board* board, Sommet<Case>* monsterVertice);
};