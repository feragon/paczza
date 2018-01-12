#include "sommet.h"

Sommet::Sommet(int x, int y) {
    _x = x;
    _y = y;
    _tomatoSmudge = true;
}
Sommet::~Sommet() {

}

std::vector<Arete*> Sommet::incidentes() {
    return _aretes_incid;
}

void Sommet::insererAreteAdj(Arete &a) {
    _aretes_incid.push_back(&a);
}

std::ostream & operator<<(std::ostream &os, Sommet const &s) {
    os << "Sommet[" << s._x << "][" << s._y << "](_tomatoSmudge=" << s._tomatoSmudge << ")";
    return os;
}