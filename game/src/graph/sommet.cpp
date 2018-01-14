#include "sommet.h"

Sommet::Sommet(int x, int y) {
    _x = x;
    _y = y;
    _tomatoSmudge = true;
}

Sommet::~Sommet() {

}

std::ostream & operator<<(std::ostream &os, Sommet const &s) {
    os << "Sommet[" << s._x << "][" << s._y << "](_tomatoSmudge=" << s._tomatoSmudge << ")";
    return os;
}