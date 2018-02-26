#pragma once

#include <graph/graphe.h>
#include "case.h"
#include "chemin.h"
#include "element.h"
#include "game/boardlistener.h"
#include <map>
#include <game/monster.h>
#include <util/listened.h>

template <typename T = int>
struct cmpPosition {
    bool operator()(const Position<T>& a, const Position<T>& b) const {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    }
};

class Board : public Graphe<Chemin, Case> {
    public:
        Board();

        inline Sommet<Case>* sommet(const Position<>& position) const;

        /**
         * @brief Place un élément au hasard sur le graphe
         * @param element Élément à placer
         * @param positionsReservees Liste des positions réservées
         * @param limit Nombre de tentatives de placement maximales
         * @throws std::runtime_exception si l'élément n'a pas pu être placé
         */
        void placerElementHasard(const Element& element, unsigned int limit = 10);

    private:
        void genererGraphe();

        unsigned int _width;
        unsigned int _height;

        std::map<Position<>, Sommet<Case>*, cmpPosition<>> _cases;
};

Sommet<Case>* Board::sommet(const Position<>& position) const {
    return _cases.at(position);
}