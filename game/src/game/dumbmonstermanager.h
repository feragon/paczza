#pragma once

#include <board/board.h>
#include "monstermanager.h"

class DumbMonsterManager : public MonsterManager {
    public:
        /**
         * @brief Crée un gestionnaire de monstres les déplaçant aléatoirement
         * @param game Jeu
         */
        DumbMonsterManager(Jeu* game);

        void moveMonster(const Monster* monster, const Position<>& playerPosition) override;

        /**
         * @brief Donne une position aléatoire à côté du sommet actuel
         * @param board Plateau
         * @param monsterVertice Sommet actuel
         * @return Nouvelle position
         */
        static Position<> getNextPosition(const Board<Element>* board, Sommet<Case<Element>>* monsterVertice);
};