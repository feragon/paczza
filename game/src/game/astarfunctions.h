#pragma once

#include <graph/graphe.h>
#include "astar/infoarete.h"
#include "astar/infosommet.h"

class AStarFunctions {
    public:
        static double hh(const Sommet<Case>* sommet);
        static Sommet<Case>* destination;
};

/**
 * @brief Libère tous les sommets du graphe
 * @param graphe Graphe
 */
void libereToutSommet(Graphe<InfoArete, InfoSommet>& graphe);

double hh(const Sommet<InfoSommet>* sommet);

Liste<std::pair<Sommet<InfoSommet>*,double>>*
listeVoisins(const Sommet<InfoSommet>* s, const Graphe<InfoArete, InfoSommet>& graphe);

Sommet<InfoSommet>*& pere(Sommet<InfoSommet>* sommet);

int& etat(Sommet<InfoSommet>* sommet);

double& c(Sommet<InfoSommet>* sommet);

double& h(Sommet<InfoSommet>* sommet);

double& g(Sommet<InfoSommet>* sommet);

bool estFinal(const Sommet<InfoSommet>* sommet);