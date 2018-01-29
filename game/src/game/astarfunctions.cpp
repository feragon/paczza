#include <board/case.h>
#include <cmath>
#include "astarfunctions.h"

Sommet<Case>* AStarFunctions::destination;

double AStarFunctions::hh(const Sommet<Case>* sommet) {
    Position<> pos = sommet->contenu().position() - destination->contenu().position();

    return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
}

bool AStarFunctions::estFinal(const Sommet<Case>* sommet) {
    return sommet == AStarFunctions::destination;
}

void libereToutSommet(Graphe<InfoArete, InfoSommet>& graphe) {
    for(Liste<Sommet<InfoSommet>>* sommets = graphe.sommets(); sommets; sommets = sommets->next) {
        sommets->value->contenu().etat() =InfoSommet::LIBRE;
    }
}

double hh(const Sommet<Case>* sommet) {
    return AStarFunctions::hh(sommet);
}

Liste<std::pair<Sommet<InfoSommet>*, double>>*
listeVoisins(const Sommet<InfoSommet>* s, const Graphe<InfoArete, InfoSommet>& graphe) {
    Liste<Sommet<InfoSommet>>* tmp = graphe.voisins(s);
    Liste<std::pair<Sommet<InfoSommet>*, double>>* res = nullptr;

    for(Liste<Sommet<InfoSommet>>* neighbors = tmp; neighbors; neighbors = neighbors->next) {
        res = new Liste<std::pair<Sommet<InfoSommet>*, double>>(new std::pair<Sommet<InfoSommet>*, double>(neighbors->value, 1), res);
    }

    Liste<Sommet<InfoSommet>>::efface1(tmp);
    return res;
}

Sommet<InfoSommet>*& pere(Sommet<InfoSommet>* sommet) {
    return sommet->contenu().parent();
}

int& etat(Sommet<InfoSommet>* sommet) {
    return sommet->contenu().etat();
}

double& c(Sommet<InfoSommet>* sommet) {
    return sommet->contenu().c();
}

double& h(Sommet<InfoSommet>* sommet) {
    return sommet->contenu().h();
}

double& g(Sommet<InfoSommet>* sommet) {
    return sommet->contenu().g();
}

bool estFinal(const Sommet<Case>* sommet) {
    return AStarFunctions::estFinal(sommet);
}
