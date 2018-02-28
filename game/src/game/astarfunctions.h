#pragma once

#include <astar/etat.h>
#include <graph/graphe.h>
#include <board/chemin.h>
#include <board/case.h>
#include "astar/infosommet.h"
#include "element.h"

class AStarFunctions {
    public:
        static double hh(const Sommet<Case<Element>>* sommet);
        static bool estFinal(const Sommet<Case<Element>>* sommet);
        static Sommet<Case<Element>>* destination;
};

/**
 * @brief Libère tous les sommets du graphe
 * @param graphe Graphe
 */
void libereToutSommet(Graphe<Chemin, Case<Element>>& graphe);

double hh(const Sommet<Case<Element>>* sommet);

Liste<std::pair<Sommet<Case<Element>>*,double>>*
listeVoisins(const Sommet<Case<Element>>* s, const Graphe<Chemin, Case<Element>>& graphe);

Sommet<Case<Element>>*& pere(Sommet<Case<Element>>* sommet);
int& etat(Sommet<Case<Element>>* sommet);
double& c(Sommet<Case<Element>>* sommet);
double& h(Sommet<Case<Element>>* sommet);
double& g(Sommet<Case<Element>>* sommet);

bool estFinal(const Sommet<Case<Element>>* sommet);

Sommet<Case<Element>>* pere(const Sommet<Case<Element>>* sommet);
int etat(const Sommet<Case<Element>>* sommet);
double c(const Sommet<Case<Element>>* sommet);
double h(const Sommet<Case<Element>>* sommet);
double g(const Sommet<Case<Element>>* sommet);