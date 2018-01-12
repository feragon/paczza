#include "arete.h"
#include "sommet.h"

Arete::Arete(Sommet &e1, Sommet &e2) {
    _extremite1 = &e1;
    _extremite2 = &e2;
    _chaleur = 0;

    e1.insererAreteAdj(*this);
    e2.insererAreteAdj(*this);
}
Arete::~Arete() {

}

void Arete::setChaleur(int chaleur) {
    if(chaleur >= 0 && chaleur < 4)
        _chaleur = chaleur;
}

std::ostream & operator<<(std::ostream &os, Arete const &a) {
    os << "Arete(" << *(a._extremite1) << "," << *(a._extremite2) << ")" << std::endl;
    return os;
}