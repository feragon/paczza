#pragma once

#include <graph/position.h>

class Joueur {
    private:
        Position _position;
    public:
        /**
         * @brief Crée un nouveau joueur
         */
        Joueur(Position p);

        Position position();
        void setPosition(Position p);
};