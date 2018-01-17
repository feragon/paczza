#pragma once

#include <graph/position.h>

class Joueur {
    private:
        Position _position;
        int _points;
    public:
        /**
         * @brief Crée un nouveau joueur
         */
        Joueur(Position p);

        Position position();
        void setPosition(Position p);
        int points();
        void addPoints(int pts);
};