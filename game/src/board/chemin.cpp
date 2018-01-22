#include "chemin.h"

Chemin::Chemin(double chaleur) {
    _chaleur = chaleur;
}

Chemin::~Chemin() {

}

bool Chemin::estAccessible() {
    return (_chaleur >= 0) ;
}

std::ostream & operator<<(std::ostream &os, const Chemin& a) {
    os << "Chemin(_chaleur=" << a._chaleur << ")";
    return os;
}