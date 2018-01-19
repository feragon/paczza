#include "case.h"

Case::Case(int points, const Position& position) {
    _position = position;
    _points = points;
}

int Case::prendrePoints() {
    int res = _points;
    _points = 0;
    return res;
}

std::ostream & operator<<(std::ostream &os, const Case& s) {
    os << "Case(" << s.position() << "; points=" << s.points() << ")";
    return os;
}