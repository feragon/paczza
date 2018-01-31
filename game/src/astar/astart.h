#pragma once
#include <graph/liste.h>
#include "etat.h"

//TODO: forward declaration ?


template <typename Graphe, typename Sommet>
class AStarT {
    public:
        static Sommet* aStar(Graphe& graphe, Sommet* depart, double(*hh)(const Sommet* s));

    private:
        static bool estPlusPetitOuEgal(const Sommet* sommet1, const Sommet* sommet2);
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
