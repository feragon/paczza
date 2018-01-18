#include "case.h"

Case::Case() {
    _points = 10;
}

Case::~Case() {

}

int Case::eatGum() {
    int pts = _points;
    _points = 0;
    return pts;
}

std::ostream & operator<<(std::ostream &os, const Case& s) {
    os << "Case()";
    return os;
}