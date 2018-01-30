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

void libereToutSommet(Graphe<Chemin, Case>& graphe) {
    for(Liste<Sommet<Case>>* sommets = graphe.sommets(); sommets; sommets = sommets->next) {
        sommets->value->contenu().etat = LIBRE;
        sommets->value->contenu().parent = nullptr;
    }
}

double hh(const Sommet<Case>* sommet) {
    return AStarFunctions::hh(sommet);
}

Liste<std::pair<Sommet<Case>*, double>>*
listeVoisins(const Sommet<Case>* s, const Graphe<Chemin, Case>& graphe) {
    Liste<Sommet<Case>>* tmp = graphe.voisins(s);
    Liste<std::pair<Sommet<Case>*, double>>* res = nullptr;

    for(Liste<Sommet<Case>>* neighbors = tmp; neighbors; neighbors = neighbors->next) {
        res = new Liste<std::pair<Sommet<Case>*, double>>(new std::pair<Sommet<Case>*, double>(neighbors->value, 1), res);
    }

    Liste<Sommet<Case>>::efface1(tmp);
    return res;
}

Sommet<Case>*& pere(Sommet<Case>* sommet) {
    return sommet->contenu().parent;
}

int& etat(Sommet<Case>* sommet) {
    return sommet->contenu().etat;
}

double& c(Sommet<Case>* sommet) {
    return sommet->contenu().c;
}

double& h(Sommet<Case>* sommet) {
    return sommet->contenu().h;
}

double& g(Sommet<Case>* sommet) {
    return sommet->contenu().g;
}

bool estFinal(const Sommet<Case>* sommet) {
    return AStarFunctions::estFinal(sommet);
}

Sommet<Case>* pere(const Sommet<Case>* sommet) {
    return sommet->contenu().parent;
}

int etat(const Sommet<Case>* sommet) {
    return sommet->contenu().etat;
}

double c(const Sommet<Case>* sommet) {
    return sommet->contenu().c;
}

double h(const Sommet<Case>* sommet) {
    return sommet->contenu().h;
}

double g(const Sommet<Case>* sommet) {
    return sommet->contenu().g;
}