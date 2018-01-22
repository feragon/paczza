#pragma once

#include <board/position.h>
#include <graph/liste.h>

class Player {
    private:
        Position<double> _position;
        Liste<Position<double>> *_deplacements;

    public:
        /**
         * @brief Crée un nouveau joueur
         */
        Player(Position<double> p);

        /**
         * @brief Donne la position du joueur
         * @return Position
         */
        inline Position<double> position() const;

        /**
         * @brief Définit la position du joueur
         * @param p Nouvelle position
         */
        inline void setPosition(Position<double> p);

        Position<double>* prochainDeplacement();
        void ajouterDeplacement(double x, double y);
        void resetDeplacement();
};

Position<double> Player::position() const {
    return _position;
}

void Player::setPosition(Position<double> p) {
    _position = p;
}