#include "arete.h"

Arete::Arete(unsigned int chaleur) {
    _chaleur = chaleur;
}

Arete::~Arete() {

}

std::ostream & operator<<(std::ostream &os, Arete const &a) {
    os << "Arete(_chaleur=" << a._chaleur << ")";
    return os;
}