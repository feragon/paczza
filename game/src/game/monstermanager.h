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
        void moveMonsters(const Position<>& playerPosition);

        /**
         * @brief Déplace le monstre donné
         * @param monster Monstre
         * @param playerPosition Position du joueur
         */
        virtual void moveMonster(const Monster* monster, const Position<>& playerPosition) = 0;

    protected:
        inline std::map<const Monster*, Position<double>>& monsters();
        inline Jeu* game() const;


    private:
        /**
         * @brief Envoie un monstre à sa position d'origine
         * @param monster Monstre
         */
        void sendHome(const Monster* monster);

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
