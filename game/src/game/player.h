#pragma once

#include <board/position.h>
#include <graph/liste.h>
#include <graph/sommet.h>
#include <board/case.h>
#include "direction.h"
#include "element.h"

class Player {
    private:
        const Sommet<Case<Element>>* _position;
        Direction _direction;
        double _avancement;

    public:
        /**
         * @brief Crée un nouveau joueur
         * @param p Position
         * @param direction Direction
         */
        Player(const Sommet<Case<Element>>* p, Direction direction);

        /**
         * @brief Donne la position du joueur
         * @return Position
         */
        inline const Sommet<Case<Element>>* position() const;

        /**
         * @brief Définit la position du joueur
         * @param p Nouvelle position
         */
        inline void setPosition(const Sommet<Case<Element>>* p);

        /**
         * @brief Donne la direction du joueur
         * @return Direction
         */
        inline Direction direction() const;

        /**
         * @brief Définit la direction du joueur
         * @param d Nouvelle direction
         */
        inline void setDirection(Direction d);

        /**
         * @brief Donne l'avancement du joueur sur son prochain déplacement
         * @return Avancement
         */
        inline double avancement() const;

        /**
         * @brief Définit l'avancement du déplacement
         * @param avancement
         */
        inline void setAvancement(double avancement);

        virtual /**
         * @brief Donne la représentation textuelle du joueur
         * @return String
         */
        std::string toString() const;

        operator std::string();

        friend std::ostream& operator << (std::ostream& o, const Player* player);
};

const Sommet<Case<Element>>* Player::position() const {
    return _position;
}

void Player::setPosition(const Sommet<Case<Element>>* p) {
    _position = p;
}

Direction Player::direction() const {
    return _direction;
}

void Player::setDirection(Direction d) {
    _direction = d;
}

double Player::avancement() const {
    return _avancement;
}

void Player::setAvancement(double avancement) {
    _avancement = avancement;
}
