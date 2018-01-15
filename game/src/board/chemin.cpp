#include "chemin.h"

Chemin::Chemin(unsigned int chaleur) {
    _chaleur = chaleur;
}

Chemin::~Chemin() {

}

std::ostream & operator<<(std::ostream &os, const Chemin& a) {
    os << "Chemin(_chaleur=" << a._chaleur << ")";
    return os;
}