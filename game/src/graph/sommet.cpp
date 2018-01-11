#include "sommet.h"

Sommet::Sommet(int x, int y) {
    _x = x;
    _y = y;
}
Sommet::~Sommet() {

}

std::vector<Arete*> Sommet::incidentes() {
    return _aretes_incid;
};