#pragma once
#include <graph/liste.h>
#include "etat.h"

template <typename Graphe, typename Sommet>
class AStarT {
    public:
        /**
         * @brief Execute l'algorithme A* sur le graphe donné
         * @param graphe Graphe
         * @param depart Départ du chemin
         * @param hh Fonction heuristique qui calcule la distance du sommet donné à la destination
         * @return Dernier sommet, égal au sommet de destination si tout s'est bien passé
         */
        static Sommet* aStar(Graphe& graphe, Sommet* depart, double(*hh)(const Sommet* s));

    private:
        /**
         * @brief Compare deux sommets
         * @param sommet1 Sommet 1
         * @param sommet2 Sommet 2
         * @return Vrai si le sommet 1 est plus proche du départ que le sommet 2
         */
        static bool estPlusPetitOuEgal(const Sommet* sommet1, const Sommet* sommet2);

        /**
         * @brief Met à jour les voisins du sommet
         * @param v Sommet voisin
         * @param s Sommet en cours de traitement
         * @param nouveauCout Nouveau coût du départ au voisin
         * @param ouverts Liste des sommets ouverts
         */
        static void miseAJourVoisin(Sommet* v, Sommet* s, const double& nouveauCout, Liste<Sommet>*& ouverts);
};

template<typename Graphe, typename Sommet>
bool AStarT<Graphe, Sommet>::estPlusPetitOuEgal(const Sommet* v1, const Sommet* v2) {
    return g(v1) <= g(v2);
}


template<typename Graphe, typename Sommet>
void AStarT<Graphe, Sommet>::miseAJourVoisin(Sommet* v, Sommet* s, const double& nouveauCout, Liste<Sommet>*& ouverts) {
    pere(v) = s;
    c(v) = nouveauCout;
    g(v) = c(v) + h(v);
    Liste<Sommet>::insertionOrdonnee(v, ouverts, estPlusPetitOuEgal);
    etat(v) = OUVERT;
}

template<typename Graphe, typename Sommet>
Sommet* AStarT<Graphe, Sommet>::aStar(Graphe& graphe, Sommet* depart, double (*hh)(const Sommet*)) {
    libereToutSommet(graphe);
    Liste<Sommet>* ouverts;

    c(depart) = 0;

    ouverts = new Liste<Sommet>(depart,NULL);
    etat(depart) = OUVERT;

    while(ouverts) {
        Sommet* s = Liste<Sommet>::depiler(ouverts);
        etat(s) = FERME;

        if(estFinal(s)) {
            Liste<Sommet>::efface1(ouverts);
            return s;
        }

        Liste<std::pair<Sommet*, double>>* tmp = listeVoisins(s, graphe);
        Liste<std::pair<Sommet*, double>>* l;

        for(l = tmp; l; l = l->next) {
            Sommet* v = l->value->first;
            double nouveauCout = c(s) + l->value->second;

            if (etat(v) == LIBRE) {
                h(v) = hh(v);
                miseAJourVoisin(v, s, nouveauCout, ouverts);
            }
            else if ( nouveauCout < c(v)) {
                if (etat(v) == OUVERT) {
                    Liste<Sommet>::retire(v, ouverts);
                }

                miseAJourVoisin(v, s, nouveauCout, ouverts);

            }
        }

        Liste<std::pair<Sommet*, double>>::efface2(tmp);
    }

    return nullptr;
}
