#pragma once

#include <graph/graphe.h>
#include "case.h"
#include "chemin.h"
#include "element.h"
#include <map>

struct cmpPosition {
    bool operator()(const Position& a, const Position& b) const {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    }
};

class Board : public Graphe<Chemin, Case> {
    public:
        Board(unsigned int width, unsigned int height, Liste<Position>* positionsReservees);

        /**
         * @brief Donne le nombre de colonnes du plateau
         * @return Nombre de colonnes
         */
        inline unsigned int width() const;

        /**
         * @brief Donne le nombre de lignes du platear
         * @return Nombre de lignes
         */
        inline unsigned int height() const;

        inline Sommet<Case>* sommet(const Position& position) const;

    private:
        void genererGraphe(Liste<Position>* positionsReservees);

        /**
         * @brief Place un élément au hasard sur le graphe
         * @param element Élément à placer
         * @param positionsReservees Liste des positions réservées
         * @param limit Nombre de tentatives de placement maximales
         * @throws std::runtime_exception si l'élément n'a pas pu être placé
         */
        void placerElementHasard(const Element& element, Liste<Position>* positionsReservees, unsigned int limit = 10);

        unsigned int _width;
        unsigned int _height;

        std::map<Position, Sommet<Case>*, cmpPosition> _cases;
        std::map<Position, Element*, cmpPosition> _elements;
};

unsigned int Board::width() const {
    return _width;
}

unsigned int Board::height() const {
    return _height;
}

Sommet<Case>* Board::sommet(const Position& position) const {
    return _cases.at(position);
}
