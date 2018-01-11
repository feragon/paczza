#include "arete.h"

Arete::Arete(Sommet *e1, Sommet *e2) {
    _extremite1 = e1;
    _extremite2 = e2;
    _chaleur = 0;
}
Arete::~Arete() {

}

void Arete::setChaleur(int chaleur) {
    if(chaleur >= 0 && chaleur < 4)
        _chaleur = chaleur;
}