#pragma once

#include <ostream>

class Position {
    public:
        double x;
        double y;

        /**
         * @brief Crée un nouveau point
         * @param x Abscisse du point
         * @param y Ordonnée du point
         */
        Position(double x = 0, double y = 0);

        bool operator==(const Position& other) const;
        bool operator!=(const Position& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Position& position);
};