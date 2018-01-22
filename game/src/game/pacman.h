#pragma once

#include "player.h"

class Pacman : public Player {
    public:
        Pacman(const Position<double>& p);

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

    private:
        int _points;
};

int Pacman::points() {
    return _points;
}

void Pacman::addPoints(int pts) {
    _points += pts;
}