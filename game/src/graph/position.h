#pragma once

#include <ostream>

class Position {
    public:
        int x;
        int y;

        /**
         * @brief Crée un nouveau point
         * @param x Abscisse du point
         * @param y Ordonnée du point
         */
        Position(int x = 0, int y = 0);

        bool operator==(const Position& other) const;
        bool operator!=(const Position& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Position& position);
};