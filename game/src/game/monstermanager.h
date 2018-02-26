#pragma once

#include <graph/liste.h>
#include <map>
#include "monster.h"

class Jeu;
class MonsterManager {
    public:
        MonsterManager(Jeu* game);

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
        inline Jeu* game() const;


    private:
        MonsterManager(const MonsterManager&);
        MonsterManager& operator = (const MonsterManager&);

        Jeu* _game;
        std::map<const Monster*, Position<double>> _newPositions;
};

std::map<const Monster*, Position<double>>& MonsterManager::monsters() {
    return _newPositions;
}

Jeu* MonsterManager::game() const {
    return _game;
}
