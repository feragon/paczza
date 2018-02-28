#pragma once

#include <graph/graphe.h>
#include "case.h"
#include "chemin.h"
#include <map>
#include <util/listened.h>
#include <algorithm>
#include <unordered_map>

template <typename ElementType>
class Board : public Graphe<Chemin, Case<ElementType>> {
    public:
        Board();

        inline Sommet<Case<ElementType>>* sommet(const Position<>& position) const;

        virtual Sommet<Case<ElementType>>* creeSommet(const Case<ElementType>& contenu) override;

        /**
         * @brief Place un élément au hasard sur le graphe
         * @param element Élément à placer
         * @param positionsReservees Liste des positions réservées
         * @param limit Nombre de tentatives de placement maximales
         * @throws std::runtime_exception si l'élément n'a pas pu être placé
         */
        void placerElementHasard(const ElementType& element, unsigned int limit = 10);

    private:
        void genererGraphe();

        std::unordered_map<Position<>, Sommet<Case<ElementType>>*> _cases;
};

template <typename ElementType>
Sommet<Case<ElementType>>* Board<ElementType>::sommet(const Position<>& position) const {
    return _cases.at(position);
}

template <typename ElementType>
Board<ElementType>::Board() {
    genererGraphe();
}

template <typename ElementType>
void Board<ElementType>::genererGraphe() {
    int width = 13;
    int height = 8;

    //Création des sommets
    for(int k = (width * height) - 1; k >= 0; k--) {
        creeSommet(Case<ElementType>(Position<>((k % width) + 1, (k / width) + 1), nullptr));
    }

    //Maison des Monstres
    this->creeArete(Chemin(-1), _cases[Position<>(7,4)], _cases[Position<>(8,4)]);
    this->creeArete(Chemin(-1), _cases[Position<>(7,5)], _cases[Position<>(7,6)]);
    this->creeArete(Chemin(-1), _cases[Position<>(6,5)], _cases[Position<>(5,5)]);
    this->creeArete(Chemin(-1), _cases[Position<>(6,4)], _cases[Position<>(6,3)]);

    //Diags
    this->creeArete(Chemin(0), _cases[Position<>(1,1)], _cases[Position<>(2,2)]);
    this->creeArete(Chemin(0), _cases[Position<>(1,8)], _cases[Position<>(2,7)]);
    this->creeArete(Chemin(0), _cases[Position<>(7,2)], _cases[Position<>(8,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(7,7)], _cases[Position<>(8,6)]);
    this->creeArete(Chemin(0), _cases[Position<>(11,1)], _cases[Position<>(12,2)]);
    this->creeArete(Chemin(0), _cases[Position<>(11,8)], _cases[Position<>(12,7)]);


    for(int j = 1; j < 8; j++)
        this->creeArete(Chemin(0), _cases[Position<>(1,j)], _cases[Position<>(1,j+1)]);

    this->creeArete(Chemin(0), _cases[Position<>(2,1)], _cases[Position<>(2,2)]);
    this->creeArete(Chemin(0), _cases[Position<>(2,8)], _cases[Position<>(2,7)]);
    this->creeArete(Chemin(0), _cases[Position<>(1,4)], _cases[Position<>(2,4)]);
    this->creeArete(Chemin(0), _cases[Position<>(1,5)], _cases[Position<>(2,5)]);
    this->creeArete(Chemin(0), _cases[Position<>(2,4)], _cases[Position<>(2,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(2,5)], _cases[Position<>(2,6)]);
    this->creeArete(Chemin(0), _cases[Position<>(2,1)], _cases[Position<>(3,1)]);
    this->creeArete(Chemin(0), _cases[Position<>(2,8)], _cases[Position<>(3,8)]);
    this->creeArete(Chemin(0), _cases[Position<>(2,3)], _cases[Position<>(3,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(2,6)], _cases[Position<>(3,6)]);

    for(int j = 2; j < 7; j++)
        this->creeArete(Chemin(0), _cases[Position<>(3,j)], _cases[Position<>(3,j+1)]);

    for(int i = 2; i < 13; i++) {
        this->creeArete(Chemin(0), _cases[Position<>(i, 2)], _cases[Position<>(i + 1, 2)]);
        this->creeArete(Chemin(0), _cases[Position<>(i, 7)], _cases[Position<>(i + 1, 7)]);
    }

    this->creeArete(Chemin(0), _cases[Position<>(3,4)], _cases[Position<>(4,4)]);
    this->creeArete(Chemin(0), _cases[Position<>(3,5)], _cases[Position<>(4,5)]);

    for(int j = 1; j < 8; j++)
        if(j!=4) this->creeArete(Chemin(0), _cases[Position<>(4,j)], _cases[Position<>(4,j+1)]);


    this->creeArete(Chemin(0), _cases[Position<>(6,1)], _cases[Position<>(6,2)]);
    this->creeArete(Chemin(0), _cases[Position<>(6,7)], _cases[Position<>(6,8)]);
    this->creeArete(Chemin(0), _cases[Position<>(8,1)], _cases[Position<>(8,2)]);
    this->creeArete(Chemin(0), _cases[Position<>(8,7)], _cases[Position<>(8,8)]);
    this->creeArete(Chemin(0), _cases[Position<>(9,1)], _cases[Position<>(9,2)]);
    this->creeArete(Chemin(0), _cases[Position<>(9,7)], _cases[Position<>(9,8)]);

    for(int j = 3; j < 6; j++) {
        this->creeArete(Chemin(0), _cases[Position<>(5, j)], _cases[Position<>(5, j+1)]);
        this->creeArete(Chemin(0), _cases[Position<>(8, j)], _cases[Position<>(8, j+1)]);
    }

    for(int i = 4; i < 8; i++) {
        this->creeArete(Chemin(0), _cases[Position<>(i, 3)], _cases[Position<>(i+1, 3)]);
        this->creeArete(Chemin(0), _cases[Position<>(i, 6)], _cases[Position<>(i+1, 6)]);
    }

    this->creeArete(Chemin(0), _cases[Position<>(6,2)], _cases[Position<>(6,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(6,6)], _cases[Position<>(6,7)]);
    this->creeArete(Chemin(0), _cases[Position<>(8,1)], _cases[Position<>(9,1)]);
    this->creeArete(Chemin(0), _cases[Position<>(8,8)], _cases[Position<>(9,8)]);
    this->creeArete(Chemin(0), _cases[Position<>(8,4)], _cases[Position<>(9,4)]);
    this->creeArete(Chemin(0), _cases[Position<>(8,5)], _cases[Position<>(9,5)]);
    this->creeArete(Chemin(0), _cases[Position<>(9,4)], _cases[Position<>(9,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(9,5)], _cases[Position<>(9,6)]);
    this->creeArete(Chemin(0), _cases[Position<>(9,3)], _cases[Position<>(10,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(9,6)], _cases[Position<>(10,6)]);

    this->creeArete(Chemin(0), _cases[Position<>(12,8)], _cases[Position<>(13,8)]);
    this->creeArete(Chemin(0), _cases[Position<>(12,1)], _cases[Position<>(13,1)]);
    this->creeArete(Chemin(0), _cases[Position<>(3,1)], _cases[Position<>(4,1)]);
    this->creeArete(Chemin(0), _cases[Position<>(3,8)], _cases[Position<>(4,8)]);

    for(int j = 1; j < 8; j++)
        this->creeArete(Chemin(0), _cases[Position<>(10,j)], _cases[Position<>(10,j+1)]);

    this->creeArete(Chemin(0), _cases[Position<>(10,4)], _cases[Position<>(11,4)]);
    this->creeArete(Chemin(0), _cases[Position<>(10,5)], _cases[Position<>(11,5)]);
    this->creeArete(Chemin(0), _cases[Position<>(11,4)], _cases[Position<>(12,4)]);
    this->creeArete(Chemin(0), _cases[Position<>(11,5)], _cases[Position<>(12,5)]);
    this->creeArete(Chemin(0), _cases[Position<>(12,2)], _cases[Position<>(12,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(12,3)], _cases[Position<>(12,4)]);
    this->creeArete(Chemin(0), _cases[Position<>(12,5)], _cases[Position<>(12,6)]);
    this->creeArete(Chemin(0), _cases[Position<>(12,6)], _cases[Position<>(12,7)]);
    this->creeArete(Chemin(0), _cases[Position<>(10,1)], _cases[Position<>(11,1)]);
    this->creeArete(Chemin(0), _cases[Position<>(11,1)], _cases[Position<>(12,1)]);
    this->creeArete(Chemin(0), _cases[Position<>(10,8)], _cases[Position<>(11,8)]);
    this->creeArete(Chemin(0), _cases[Position<>(11,8)], _cases[Position<>(12,8)]);
    this->creeArete(Chemin(0), _cases[Position<>(13,1)], _cases[Position<>(13,2)]);
    this->creeArete(Chemin(0), _cases[Position<>(13,2)], _cases[Position<>(13,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(13,6)], _cases[Position<>(13,7)]);
    this->creeArete(Chemin(0), _cases[Position<>(13,7)], _cases[Position<>(13,8)]);
    this->creeArete(Chemin(0), _cases[Position<>(12,3)], _cases[Position<>(13,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(12,6)], _cases[Position<>(13,6)]);
    this->creeArete(Chemin(0), _cases[Position<>(11,3)], _cases[Position<>(12,3)]);
    this->creeArete(Chemin(0), _cases[Position<>(11,6)], _cases[Position<>(12,6)]);
}

template <typename ElementType>
void Board<ElementType>::placerElementHasard(const ElementType& element, unsigned int limit) {
    srand(time(NULL));
    unsigned int i = 0;
    unsigned long bucket, bucket_size;

    Case<ElementType>* c = nullptr;

    do {
        if(i == limit) {
            throw std::runtime_error("Impossible de placer les éléments");
        }

        do {
            bucket = rand() % _cases.bucket_count();
        }
        while ((bucket_size = _cases.bucket_size(bucket)) == 0 );

        c = &(std::next(_cases.begin(bucket), rand() % bucket_size)->second->contenu());

        i++;
    } while(c->element());

    c->setElement(&element);
}

template<typename ElementType>
Sommet<Case<ElementType>>* Board<ElementType>::creeSommet(const Case<ElementType>& contenu) {
    Sommet<Case<ElementType>>* vertex = Graphe<Chemin, Case<ElementType>>::creeSommet(contenu);
    _cases[contenu.position()] = vertex;

    return vertex;
}