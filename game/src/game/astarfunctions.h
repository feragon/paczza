#pragma once

#include <astar/etat.h>
#include <graph/graphe.h>
#include <board/chemin.h>
#include <board/case.h>
#include "astar/infosommet.h"
#include "element.h"

class AStarFunctions {
    public:
        /**
         * @brief Donne le coût heuristique du sommet donné jusqu'à la destination
         * @param sommet Sommet
         * @return Coût de sommet à destination
         */
        static double hh(const Sommet<Case<Element>>* sommet);

        /**
         * @param sommet Sommet
         * @return Vrai si le sommet est le sommet final
         */
        static bool estFinal(const Sommet<Case<Element>>* sommet);
        static Sommet<Case<Element>>* destination;
};

/**
 * @brief Libère tous les sommets du graphe
 * @param graphe Graphe
 */
void libereToutSommet(Graphe<Chemin, Case<Element>>& graphe);

/**
 * @brief Donne le coût heuristique
 * @param sommet Sommet
 * @return Coût heuristique
 */
double hh(const Sommet<Case<Element>>* sommet);

/**
 * @brief Donne la liste des voisins du sommet
 * @param s Sommet
 * @param graphe Graphe
 * @return Liste des voisins
 */
Liste<std::pair<Sommet<Case<Element>>*,double>>*
listeVoisins(const Sommet<Case<Element>>* s, const Graphe<Chemin, Case<Element>>& graphe);

/**
 * @brief Donne le père du sommet
 * @param sommet Sommet
 * @return Père
 */
Sommet<Case<Element>>*& pere(Sommet<Case<Element>>* sommet);

/**
 * @brief Donne l'état du sommet
 * @param sommet Sommet
 * @return État
 */
int& etat(Sommet<Case<Element>>* sommet);

/**
 * @brief Donne le coût du départ au sommet
 * @param sommet Sommet
 * @return Coût
 */
double& c(Sommet<Case<Element>>* sommet);

/**
 * @brief Donne le coût heuristique du sommet à la destination
 * @param sommet Sommet
 * @return Coût
 */
double& h(Sommet<Case<Element>>* sommet);

/**
 * @brief Donne le coût du départ jusqu'à la destination en passant par le sommet
 * @param sommet Sommet
 * @return Coût
 */
double& g(Sommet<Case<Element>>* sommet);

/**
 * @param sommet Sommet
 * @return Vrai si le sommet est final
 */
bool estFinal(const Sommet<Case<Element>>* sommet);

/**
 * @brief Donne le père du sommet
 * @param sommet Sommet
 * @return Père
 */
Sommet<Case<Element>>* pere(const Sommet<Case<Element>>* sommet);

/**
 * @brief Donne l'état du sommet
 * @param sommet Sommet
 * @return État
 */
int etat(const Sommet<Case<Element>>* sommet);

/**
 * @brief Donne le coût du départ au sommet
 * @param sommet Sommet
 * @return Coût
 */
double c(const Sommet<Case<Element>>* sommet);

/**
 * @brief Donne le coût heuristique du sommet à la destination
 * @param sommet Sommet
 * @return Coût
 */
double h(const Sommet<Case<Element>>* sommet);

/**
 * @brief Donne le coût du départ jusqu'à la destination en passant par le sommet
 * @param sommet Sommet
 * @return Coût
 */
double g(const Sommet<Case<Element>>* sommet);