#include "case.h"

Case::Case(const Position& position) {
    _position = position;
}

std::ostream & operator<<(std::ostream &os, const Case& s) {
    os << "Case(" << s.position() << ")";
    return os;
}
