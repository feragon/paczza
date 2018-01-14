#include "sommet.h"

Sommet::Sommet(int colonne, int ligne) {
    _column = colonne;
    _row = ligne;
    _tomatoSmudge = true;
}

Sommet::~Sommet() {

}

std::ostream & operator<<(std::ostream &os, Sommet const &s) {
    os << "Sommet[" << s._column << "][" << s._row << "](_tomatoSmudge=" << s._tomatoSmudge << ")";
    return os;
}