#pragma once

#include <graph/graphe.h>
#include "infoarete.h"
#include "infosommet.h"

/**
 * @brief Libère tous les sommets du graphe
 * @param graphe Graphe
 */
void libereToutSommet(Graphe<InfoArete, InfoSommet>& graphe);

double hh(const Sommet<InfoSommet>*);

Liste<std::pair<Sommet<InfoSommet>*,double>>*
listeVoisins(const Sommet<InfoSommet>* s, const Graphe<InfoArete, InfoSommet>& graphe);

Sommet<InfoSommet>*& pere(Sommet<InfoSommet>* sommet);

int& etat(Sommet<InfoSommet>* sommet);

double& c(Sommet<InfoSommet>* sommet);

double& h(Sommet<InfoSommet>* sommet);

double& g(Sommet<InfoSommet>* sommet);

bool estFinal(const Sommet<InfoSommet>* sommet);