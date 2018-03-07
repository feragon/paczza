#pragma once

#include "monstermanager.h"

class SenseMonsterManager : public MonsterManager {
    public:
        /**
         * @brief Crée un gestionnaire de monstre utilisant la vue et le flair
         * @param game Jeu associé
         */
        SenseMonsterManager(Jeu* game);

        void moveMonster(const Monster* monster, const Position<>& playerPosition) override;

    private:
        /**
         * @brief Donne la position
         * @param playerPosition Position du joueur
         * @param position Sommet du monstre
         * @return Position d'une case adjacente plus proche du joueur
         * @throws PlayerNotInSight si le joueur n'est pas vu par le monstre
         */
        Position<> nextPositionBySight(const Sommet<Case<Element>>* monsterVertice, const Position<>& playerPosition);

        /**
         * @brief Donne la prochaine position en se basant sur la chaleur
         * @param monsterVertice Sommet du monstre
         * @return Position suivant l'arête la plus chaude
         * @throws
         */
        Position<> nextPositionByHeat(const Sommet<Case<Element>>* monsterVertice);
};