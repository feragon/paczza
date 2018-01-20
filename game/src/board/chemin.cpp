#include "chemin.h"

Chemin::Chemin(double chaleur) {
    _chaleur = chaleur;
}

Chemin::~Chemin() {

}

std::ostream & operator<<(std::ostream &os, const Chemin& a) {
    os << "Chemin(_chaleur=" << a._chaleur << ")";
    return os;
}