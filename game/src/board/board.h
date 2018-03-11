#pragma once

#include <graph/graphe.h>
#include "case.h"
#include "chemin.h"
#include <map>
#include <util/listened.h>
#include <algorithm>
#include <unordered_map>
#include <time.h>

template <typename ElementType>
class Board : public Graphe<Chemin, Case<ElementType>> {
    public:
        /**
         * @brief Crée un plateau vide
         */
        Board();

        /**
         * @brief Donne le sommet associé à une position
         * @param position Position
         * @return Sommet
         * @throw std::out_of_range si la position n'existe pas dans le graphe
         */
        inline Sommet<Case<ElementType>>* sommet(const Position<>& position) const;

        virtual Sommet<Case<ElementType>>* creeSommet(const Case<ElementType>& contenu) override;

        /**
         * @brief Place un élément au hasard sur le graphe
         * @param element Élément à placer
         * @param limit Nombre de tentatives de placement maximales
         * @throws std::runtime_exception si l'élément n'a pas pu être placé
         */
        void placerElementHasard(const ElementType& element, unsigned int limit = 10);

        Arete<Chemin, Case<ElementType>>*
        creeArete(const Chemin& contenu, Sommet<Case<ElementType>>* debut, Sommet<Case<ElementType>>* fin) override;

    private:
        std::unordered_map<Position<>, Sommet<Case<ElementType>>*> _cases;
};

template <typename ElementType>
Sommet<Case<ElementType>>* Board<ElementType>::sommet(const Position<>& position) const {
    return _cases.at(position);
}

template <typename ElementType>
Board<ElementType>::Board() {

}

template <typename ElementType>
void Board<ElementType>::placerElementHasard(const ElementType& element, unsigned int limit) {
    srand(time(NULL));
    unsigned int i = 0;
    unsigned long bucket, bucket_size;

    Case<ElementType>* c = nullptr;
    Sommet<Case<ElementType>>* s = nullptr;

    do {
        if(i == limit) {
            throw std::runtime_error("Impossible de placer les éléments");
        }

        do {
            bucket = rand() % _cases.bucket_count();
        }
        while ((bucket_size = _cases.bucket_size(bucket)) == 0 );

        s = *&(std::next(_cases.begin(bucket), rand() % bucket_size)->second);
        c = &s->contenu();

        i++;
    } while(c->element() || s->degre() == 0);

    c->setElement(&element);
}

template<typename ElementType>
Sommet<Case<ElementType>>* Board<ElementType>::creeSommet(const Case<ElementType>& contenu) {
    Sommet<Case<ElementType>>* vertex = Graphe<Chemin, Case<ElementType>>::creeSommet(contenu);
    _cases[contenu.position()] = vertex;

    return vertex;
}

template<typename ElementType>
Arete<Chemin, Case<ElementType>>* Board<ElementType>::creeArete(const Chemin& contenu, Sommet<Case<ElementType>>* debut, Sommet<Case<ElementType>>* fin) {
    Position<> diff = debut->contenu().position() - fin->contenu().position();

    if(abs(diff.x) > 1 || abs(diff.y) > 1) {
        throw std::runtime_error("La distance d'une arête ne peut excéder 1");
    }

    return Graphe<Chemin, Case<ElementType>>::creeArete(contenu, debut, fin);
}
