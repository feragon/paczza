#include "fonctions.h"

void libereToutSommet(Graphe<InfoArete, InfoSommet>& graphe) {
    for(Liste<Sommet<InfoSommet>>* sommets = graphe.sommets(); sommets; sommets = sommets->next) {
        sommets->value->contenu().setEtat(InfoSommet::LIBRE);
    }
}

double hh(const Sommet<InfoSommet>* sommet) {
    return 0;
}

Liste<std::pair<Sommet<InfoSommet>*, double>>*
listeVoisins(const Sommet<InfoSommet>* s, const Graphe<InfoArete, InfoSommet>& graphe) {
    return nullptr;
}

Sommet<InfoSommet>*& pere(Sommet<InfoSommet>* sommet) {
    return <#initializer#>;
}

int& etat(Sommet<InfoSommet>* sommet) {
    return <#initializer#>;
}

double& c(Sommet<InfoSommet>* sommet) {
    return <#initializer#>;
}

double& h(Sommet<InfoSommet>* sommet) {
    return <#initializer#>;
}

double& g(Sommet<InfoSommet>* sommet) {
    return <#initializer#>;
}

bool estFinal(const Sommet<InfoSommet>* sommet) {
    return false;
}
