#include "position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

std::ostream& operator<<(std::ostream& os, const Position& position) {
    os << "Position(" << position.x << ";" << position.y << ")";
    return os;
}

bool Position::operator==(const Position& other) const {
    return x == other.x &&
           y == other.y;
}

bool Position::operator!=(const Position& other) const {
    return !(other == *this);
}
