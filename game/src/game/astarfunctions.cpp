#include <board/case.h>
#include <cmath>
#include "astarfunctions.h"

double AStarFunctions::hh(const Sommet<Case>* sommet) {
    Position<> pos = sommet->contenu().position() - destination->contenu().position();

    return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
}

void libereToutSommet(Graphe<InfoArete, InfoSommet>& graphe) {
    for(Liste<Sommet<InfoSommet>>* sommets = graphe.sommets(); sommets; sommets = sommets->next) {
        sommets->value->contenu().setEtat(InfoSommet::LIBRE);
    }
}

double hh(const Sommet<InfoSommet>* sommet) {
    return AStarFunctions::hh(sommet);
}

Liste<std::pair<Sommet<InfoSommet>*, double>>*
listeVoisins(const Sommet<InfoSommet>* s, const Graphe<InfoArete, InfoSommet>& graphe) {
    return nullptr;
}

Sommet<InfoSommet>*& pere(Sommet<InfoSommet>* sommet) {
    return sommet;
}

int& etat(Sommet<InfoSommet>* sommet) {
    int e;
    return e;
}

double& c(Sommet<InfoSommet>* sommet) {
    double c;
    return c;
}

double& h(Sommet<InfoSommet>* sommet) {
    double h;
    return h;
}

double& g(Sommet<InfoSommet>* sommet) {
    double g;
    return g;
}

bool estFinal(const Sommet<InfoSommet>* sommet) {
    return false;
}
