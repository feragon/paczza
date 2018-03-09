#pragma once

#include <iostream>
#include <vector>
#include "sommet.h"
#include "arete.h"
#include "liste.h"

template <class T>
class SommetClesEgales {
    private:
        Sommet<T>* _sommet;

    public:
        /**
         * @brief Crée un foncteur de comparaison de sommets
         * @param sommet Sommet de comparaison
         */
        SommetClesEgales(Sommet<T>* sommet) {
            _sommet = sommet;
        }

        /**
         * @brief Compare le sommet donné au sommet d'origine
         * @param autre Autre sommet
         * @return Vrai s'ils sont égaux
         */
        bool operator() (const Sommet<T>* autre) {
            return _sommet->cle() == autre->cle();
        }
};

template<class S, class T>
class Graphe {
    private:
        /**
         * @brief Vide le graphe
         */
        void reset();

        /**
         * @brief Copie un graphe
         * @param graphe Graphe à copier
         */
        void copie(const Graphe& graphe);

        /**
         * @brief Crée un sommet dans le graphe
         * @param cle Clé du sommet
         * @param content Contenu du sommet
         * @return Nouveau sommet
         */
        Sommet<T>* creerSommet(int cle, const T& content);

        Liste<Sommet<T>>* _sommets;
        Liste<Arete<S,T>>* _aretes;
        int _prochaineCle;

    public:
        /**
         * @brief Crée un graphe
         */
        Graphe();
        Graphe(const Graphe& graphe);
        virtual ~Graphe();

        Graphe<S,T>& operator = (const Graphe& graphe);

        /**
         * @brief Crée un sommet isolé
         * @param contenu du sommet
         * @return Nouveau sommet
         */
        virtual Sommet<T>* creeSommet(const T& contenu);

        virtual /**
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
         */
        Liste<Sommet<T>>* sommets();

        /**
         * @brief Donne la liste des arêtes du graphe
         * @return Liste des arêtes du graphe
         */
        Liste<Arete<S, T>>* aretes();

        /**
         * @brief Retourne l'arrête contenant les deux sommets
         * @param s1 Sommet 1
         * @param s2 Sommet 2
         * @return Arête
         */
        Arete<S,T>* getAreteParSommets(const Sommet<T>* s1, const Sommet<T>* s2) const;

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
Graphe<S,T>::Graphe(const Graphe& graphe) :
        Graphe() {
    copie(graphe);
}

template <class S, class T>
Graphe<S,T>::~Graphe() {
    reset();
}

template <class S, class T>
Graphe<S, T>& Graphe<S,T>::operator=(const Graphe& graphe) {
    reset();
    copie(graphe);
    return *this;
}

template <class S, class T>
void Graphe<S,T>::reset() {
    Liste<Arete<S, T>>::efface2(_aretes);
    Liste<Sommet<T>>::efface2(_sommets);
    _prochaineCle = 0;
}

template <class S, class T>
void Graphe<S,T>::copie(const Graphe& graphe) {
    Liste<Sommet<T>>* l;

    for(l = graphe._sommets; l; l = l->next) {
        creerSommet(l->value->cle(), l->value->contenu());
    }

    Liste<Arete<S,T>>* a;
    for(a = graphe._aretes; a; a = a->next) {
        SommetClesEgales<T> conditionDebut(a->value->debut());
        SommetClesEgales<T> conditionFin(a->value->fin());

        Sommet<T>* debut = Liste<Sommet<T>>::appartient(_sommets, conditionDebut)->value;
        Sommet<T>* fin = Liste<Sommet<T>>::appartient(_sommets, conditionFin)->value;
        creeArete(a->value, debut, fin);
    }
}

template <class S, class T>
Sommet<T>* Graphe<S,T>::creerSommet(int cle, const T& content) {
    Sommet<T>* sommet = new Sommet<T>(cle, content);

    _sommets = new Liste<Sommet<T>>(sommet, _sommets);

    return sommet;
}

template <class S, class T>
Sommet<T>* Graphe<S,T>::creeSommet(const T& contenu) {
    return creerSommet(_prochaineCle++, contenu);
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
                    new std::pair<Sommet<T>*, Arete<S, T>*>(arete->value->fin(), arete->value),
                    res
            );
        }
        else if(arete->value->fin() == sommet) {
            res = new Liste<std::pair<Sommet<T>*, Arete<S, T>*>>(
                    new std::pair<Sommet<T>*, Arete<S, T>*>(arete->value->debut(), arete->value),
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

template<class S, class T>
Arete<S, T>* Graphe<S,T>::getAreteParSommets(const Sommet<T>* s1, const Sommet<T>* s2) const {
    Liste<Arete<S,T>>* l;

    for(l = this->_aretes; l; l = l->next) {
        if (l->value->estEgal(s1, s2)) {
            return l->value;
        }
    }

    return NULL;
}
