#pragma once

#include <graph/liste.h>
#include <map>
#include <board/board.h>
#include "monster.h"

class MonsterManager {
    public:
        MonsterManager(const Board* board);

        /**
         * @brief Ajoute un monstre
         * @param monster Nouveau monstre
         */
        void addMonster(const Monster* monster);

        /**
         * @brief Retourne la novuvelle position du monstre
         * @param monster Monstre
         * @return Nouvelle position
         */
        Position newPosition(const Monster* monster) const;

        /**
         * @brief Supprime un monstre
         * @param monster Monstre
         */
        void removeMonster(const Monster* monster);

        /**
         * @brief Déplace les monstres gérés
         */
        virtual void moveMonsters() = 0;

    protected:
        inline std::map<const Monster*, Position>& monsters();
        inline const Board* board() const;

    private:
        MonsterManager(const MonsterManager&);
        MonsterManager& operator = (const MonsterManager&);

        const Board* _board;
        std::map<const Monster*, Position> _newPositions;
};

std::map<const Monster*, Position>& MonsterManager::monsters() {
    return _newPositions;
}

const Board* MonsterManager::board() const {
    return _board;
}
