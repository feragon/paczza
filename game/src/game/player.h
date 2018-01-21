#pragma once

#include <graph/position.h>
#include <graph/liste.h>

class Player {
    private:
        Position _position;
        Liste<Position> *_deplacements;

    public:
        /**
         * @brief Crée un nouveau joueur
         */
        Player(Position p);

        /**
         * @brief Donne la position du joueur
         * @return Position
         */
        inline Position position() const;

        /**
         * @brief Définit la position du joueur
         * @param p Nouvelle position
         */
        inline void setPosition(Position p);

        Position* prochainDeplacement();
        void ajouterDeplacement(double x, double y);
        void resetDeplacement();
};

Position Player::position() const {
    return _position;
}

void Player::setPosition(Position p) {
    _position = p;
}