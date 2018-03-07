#include <cmath>
#include "astarfunctions.h"

Sommet<Case<Element>>* AStarFunctions::destination;

double AStarFunctions::hh(const Sommet<Case<Element>>* sommet) {
    Position<> pos = sommet->contenu().position() - destination->contenu().position();

    return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
}

bool AStarFunctions::estFinal(const Sommet<Case<Element>>* sommet) {
    return sommet == AStarFunctions::destination;
}

void libereToutSommet(Graphe<Chemin, Case<Element>>& graphe) {
    for(Liste<Sommet<Case<Element>>>* sommets = graphe.sommets(); sommets; sommets = sommets->next) {
        sommets->value->contenu().etat = LIBRE;
        sommets->value->contenu().parent = nullptr;
    }
}

double hh(const Sommet<Case<Element>>* sommet) {
    return AStarFunctions::hh(sommet);
}

Liste<std::pair<Sommet<Case<Element>>*, double>>*
listeVoisins(const Sommet<Case<Element>>* s, const Graphe<Chemin, Case<Element>>& graphe) {
    Liste<Sommet<Case<Element>>>* tmp = graphe.voisins(s);
    Liste<std::pair<Sommet<Case<Element>>*, double>>* res = nullptr;

    for(Liste<Sommet<Case<Element>>>* neighbors = tmp; neighbors; neighbors = neighbors->next) {
        res = new Liste<std::pair<Sommet<Case<Element>>*, double>>(new std::pair<Sommet<Case<Element>>*, double>(neighbors->value, 1), res);
    }

    Liste<Sommet<Case<Element>>>::efface1(tmp);
    return res;
}

Sommet<Case<Element>>*& pere(Sommet<Case<Element>>* sommet) {
    return sommet->contenu().parent;
}

int& etat(Sommet<Case<Element>>* sommet) {
    return sommet->contenu().etat;
}

double& c(Sommet<Case<Element>>* sommet) {
    return sommet->contenu().c;
}

double& h(Sommet<Case<Element>>* sommet) {
    return sommet->contenu().h;
}

double& g(Sommet<Case<Element>>* sommet) {
    return sommet->contenu().g;
}

bool estFinal(const Sommet<Case<Element>>* sommet) {
    return AStarFunctions::estFinal(sommet);
}

Sommet<Case<Element>>* pere(const Sommet<Case<Element>>* sommet) {
    return sommet->contenu().parent;
}

int etat(const Sommet<Case<Element>>* sommet) {
    return sommet->contenu().etat;
}

double c(const Sommet<Case<Element>>* sommet) {
    return sommet->contenu().c;
}

double h(const Sommet<Case<Element>>* sommet) {
    return sommet->contenu().h;
}

double g(const Sommet<Case<Element>>* sommet) {
    return sommet->contenu().g;
}