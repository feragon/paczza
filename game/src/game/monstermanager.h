#pragma once

#include <graph/liste.h>
#include <map>
#include <board/board.h>
#include "monster.h"

class MonsterManager {
    public:
        MonsterManager(Board* board);

        /**
         * @brief Retourne la novuvelle position du monstre
         * @param monster Monstre
         * @return Nouvelle position
         */
        Position<double> newPosition(const Monster* monster) const;

        /**
         * @brief Déplace les monstres gérés
         */
        virtual void moveMonsters(const Position<>& playerPosition) = 0;

    protected:
        inline std::map<const Monster*, Position<double>>& monsters();
        inline Board* board() const;


    private:
        MonsterManager(const MonsterManager&);
        MonsterManager& operator = (const MonsterManager&);

        Board* _board;
        std::map<const Monster*, Position<double>> _newPositions;
};

std::map<const Monster*, Position<double>>& MonsterManager::monsters() {
    return _newPositions;
}

Board* MonsterManager::board() const {
    return _board;
}
