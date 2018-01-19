#pragma once

#include <ostream>
#include <graph/position.h>

class Case {
    private:
        int _points;
        Position _position;

    public:
        Case(int points, const Position& position);

        /**
         * @brief Donne la position de la case
         * @return Position
         */
        inline Position position() const;

        /**
         * @brief Donne le nombre de points, ou 0 si la case est vide
         * @return Nombre de points
         */
        inline int points() const;

        /**
         * @brief Définit le nombre de points, ou 0 pour vider la case
         * @param points Nouveau nombre de points
         */
        inline void setPoints(int points);

        /**
         * @brief Donne le nombre de points et le remet à 0
         * @return Nombre de points pris
         */
        int prendrePoints();

        /**
         * @brief Définit la nouvelle position de la case
         * @param position Nouvelle position
         */
        inline void setPosition(const Position& position);

        friend std::ostream& operator<<(std::ostream &, const Case&);
};

Position Case::position() const {
    return _position;
}

void Case::setPosition(const Position& position) {
    _position = position;
}

int Case::points() const {
    return _points;
}

void Case::setPoints(int points) {
    _points = points;
}