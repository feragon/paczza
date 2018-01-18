#pragma once

#include <ostream>
#include <graph/position.h>

class Case {
    private:
        int _points;
        Position _position;

    public:
        Case(const Position& position);

        /**
         * @brief Donne la position de la case
         * @return Position
         */
        inline Position position() const;

        /**
         * @brief Définit la nouvelle position de la case
         * @param position Nouvelle position
         */
        inline void setPosition(const Position& position);

        int eatGum();

        friend std::ostream& operator<<(std::ostream &, const Case&);
};

Position Case::position() const {
    return _position;
}

void Case::setPosition(const Position& position) {
    _position = position;
}
