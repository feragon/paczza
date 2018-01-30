#pragma once
#include <graph/liste.h>

enum Etat {
    LIBRE,
    OUVERT,
    FERME
};

template <typename Graphe, typename Sommet>
class AStarT {
    public:
        inline static Sommet* aStar(Graphe& graphe, Sommet* depart, double(*hh)(const Sommet* s));
};

template<typename Graphe, typename Sommet>
Sommet* AStarT<Graphe, Sommet>::aStar(Graphe& graphe, Sommet* depart, double (*hh)(const Sommet*)) {
    libereTousSommet(graphe);
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

        for(l = tmp; l; l = l->s) {
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
