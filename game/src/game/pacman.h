#pragma once

#include "player.h"

class Pacman : public Player {
    public:
        Pacman(const Position<double>& p, unsigned short nbLifes);

        /**
         * @brief Donne le nombre de points
         * @return Nombre de points
         */
        inline int points();

        /**
         * @brief Ajoute des points
         * @param pts Nombre de points
         */
        inline void addPoints(int pts);

        /**
         * @brief Donne le nombre de vies restantes du joueur
         * @return Nombre de vies
         */
        inline unsigned short nbLifes() const;

        /**
         * @brief Retire une vie au joueur
         */
         void takeLife();

    private:
        int _points;
        unsigned short _nbLifes;
};

int Pacman::points() {
    return _points;
}

void Pacman::addPoints(int pts) {
    _points += pts;
}

unsigned short Pacman::nbLifes() const {
    return _nbLifes;
}
