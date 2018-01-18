#pragma once

#include <iostream>
#include <vector>
#include "sommet.h"
#include "arete.h"
#include "liste.h"

//TODO: ajout méthodes manquantes TD

template<class S, class T>
class Graphe {
    private:
        Liste<Sommet<T>>* _sommets;
        Liste<Arete<S,T>>* _aretes;
        int _prochaineCle;

    public:
        Graphe();
        virtual ~Graphe();

        /**
         * @brief Crée un sommet isolé
         * @param contenu du sommet
         * @return Nouveau sommet
         */
        Sommet<T>* creeSommet(const T& contenu);

        /**
         * @brief Crée une arête entre 2 sommets supposés existants
         * @param contenu Contenu de l'arête
         * @param debut Sommet de début
         * @param fin Sommet de fin
         * @return Nouvelle arête
         */
        Arete<S,T>* creeArete(const S& contenu, Sommet<T>* debut, Sommet<T>* fin);

        /**
         * @brief Donne le nombre de sommets dans le graphe
         * @return Nombre de sommets dans le graphe
         */
        int nombreSommets() const;

        /**
         * @brief Donne le nombre d'arêtes dans le graphe
         * @return Nombre d'arêtes dans le graphe
         */
        int nombreAretes() const;

        /**
         * @brief Donne la liste des arêtes et sommets adjacents au sommet donné
         * @param sommet Sommet
         * @return Arrêtes et sommets adjacents
         */
        Liste<std::pair<Sommet<T>*, Arete<S,T>*>>* adjacences(const Sommet<T>* sommet) const;

        /**
         * @brief Donne la liste des arêtes adjacentes au sommet
         * @param sommet Sommet
         * @return Arêtes adjacentes
         */
        Liste<Arete<S,T>>*  aretesAdjacentes(const Sommet<T>* sommet) const;

        /**
         * @brief Donne la liste de tous les sommets voisins du sommet
         * @param sommet Sommet
         * @return Sommets voisins
         */
        Liste<Sommet<T>>*  voisins(const Sommet<T>* sommet) const;

        /**
         * @brief Donne la liste des sommets du graphe
         * @return Liste des sommets du graphe
         * @TODO: garder ? const ?
         */
        Liste<Sommet<T>>* sommets();

        /**
         * @brief Donne la liste des arêtes du graphe
         * @return Liste des arêtes du graphe
         * @TODO: garder ? const ?
         */
        Liste<Arete<S, T>>* aretes();

        operator std::string() const;

        template <class osS, class osT>
        friend std::ostream& operator << (std::ostream& o, const Graphe<osS,osT>& g);
};


template <class S, class T>
Graphe<S,T>::Graphe() {
    _sommets = nullptr;
    _aretes = nullptr;
    _prochaineCle = 0;
}

template <class S, class T>
Graphe<S,T>::~Graphe() {
    //TODO
}

template <class S, class T>
Sommet<T>* Graphe<S,T>::creeSommet(const T& contenu) {
    Sommet<T>* sommet = new Sommet<T>(_prochaineCle++, contenu);

    _sommets = new Liste<Sommet<T>>(sommet, _sommets);

    return sommet;
}

template <class S, class T>
Arete<S, T>* Graphe<S, T>::creeArete(const S& contenu, Sommet<T>* debut, Sommet<T>* fin) {
    Arete<S,T>* arete = new Arete<S,T>(0, contenu, debut, fin);

    _aretes = new Liste<Arete<S,T>>(arete, _aretes);

    return arete;
}

template <class S, class T>
int Graphe<S, T>::nombreSommets() const {
    return Liste<Sommet<T>>::taille(_sommets);
}

template <class S, class T>
int Graphe<S, T>::nombreAretes() const {
    return Liste<Arete<S,T>>::taille(_aretes);
}

template <class S, class T>
Graphe<S, T>::operator std::string() const {
    std::ostringstream oss;

    oss << "Graphe(sommets=" << Liste<Sommet<T>>::toString(_sommets) <<
                "; aretes=" << Liste<Arete<S,T>>::toString(_aretes) << ")";

    return oss.str();
}

template<class S, class T>
std::ostream& operator<<(std::ostream& o, const Graphe<S, T>& g) {
    o << (std::string) g;
    return o;
}

template<class S, class T>
Liste<std::pair<Sommet<T>*, Arete<S, T>*>>* Graphe<S,T>::adjacences(const Sommet<T>* sommet) const {
    Liste<std::pair<Sommet<T>*, Arete<S, T>*>>* res = nullptr;

    for(Liste<Arete<S,T>>* arete = _aretes; arete; arete = arete->next) {
        if(arete->value->debut() == sommet) {
            res = new Liste<std::pair<Sommet<T>*, Arete<S, T>*>>(
                    std::make_pair<Sommet<T>*, Arete<S, T>*>(arete->value->fin(), arete->value),
                    res
            );
        }
        else if(arete->value->fin() == sommet) {
            res = new Liste<std::pair<Sommet<T>*, Arete<S, T>*>>(
                    std::make_pair<Sommet<T>*, Arete<S, T>*>(arete->value->debut(), arete->value),
                    res
            );
        }
    }

    return res;
}

template<class S, class T>
Liste<Arete<S, T>>* Graphe<S,T>::aretesAdjacentes(const Sommet<T>* sommet) const {
    Liste<Arete<S, T>>* res = nullptr;

    for(Liste<Arete<S,T>>* arete = _aretes; arete; arete = arete->next) {
        if(arete->value->debut() == sommet || arete->value->fin() == sommet) {
            res = new Liste<Arete<S,T>>(arete->value, res);
        }
    }

    return res;
}

template<class S, class T>
Liste<Sommet<T>>* Graphe<S,T>::voisins(const Sommet<T>* sommet) const {
    Liste<Sommet<T>>* res = nullptr;

    for(Liste<Arete<S,T>>* arete = _aretes; arete; arete = arete->next) {
        if(arete->value->debut() == sommet) {
            res = new Liste<Sommet<T>>(arete->value->fin(), res);
        }
        else if(arete->value->fin() == sommet) {
            res = new Liste<Sommet<T>>(arete->value->debut(), res);
        }
    }

    return res;
}

template<class S, class T>
Liste<Sommet<T>>* Graphe<S,T>::sommets() {
    return _sommets;
}

template<class S, class T>
Liste<Arete<S, T>>* Graphe<S,T>::aretes() {
    return _aretes;
}
