#pragma once

#include <astar/etat.h>
#include <graph/graphe.h>
#include <board/chemin.h>
#include <board/case.h>
#include "astar/infosommet.h"

class AStarFunctions {
    public:
        static double hh(const Sommet<Case>* sommet);
        static bool estFinal(const Sommet<Case>* sommet);
        static Sommet<Case>* destination;
};

/**
 * @brief Libère tous les sommets du graphe
 * @param graphe Graphe
 */
void libereToutSommet(Graphe<Chemin, Case>& graphe);

double hh(const Sommet<Case>* sommet);

Liste<std::pair<Sommet<Case>*,double>>*
listeVoisins(const Sommet<Case>* s, const Graphe<Chemin, Case>& graphe);

Sommet<Case>*& pere(Sommet<Case>* sommet);
int& etat(Sommet<Case>* sommet);
double& c(Sommet<Case>* sommet);
double& h(Sommet<Case>* sommet);
double& g(Sommet<Case>* sommet);

bool estFinal(const Sommet<Case>* sommet);

Sommet<Case>* pere(const Sommet<Case>* sommet);
int etat(const Sommet<Case>* sommet);
double c(const Sommet<Case>* sommet);
double h(const Sommet<Case>* sommet);
double g(const Sommet<Case>* sommet);