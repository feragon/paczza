#include "case.h"

Case::Case(const Position& position) {
    _position = position;
    _points = 10;
}

int Case::eatGum() {
    int pts = _points;
    _points = 0;
    return pts;
}

std::ostream & operator<<(std::ostream &os, const Case& s) {
    os << "Case(" << s.position() << ")";
    return os;
}
