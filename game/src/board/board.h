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
         * @brief Donne le joueur
         * @return Pacman
         */
        inline Pacman& player();

        /**
         * @brief Donne le joueur
         * @return Pacman constant
         */
        inline const Pacman& player() const;

        /**
         * @brief Donne la liste des monstres sur le plateau
         * @return Liste de monstres
         */
        inline Liste<Monster>* monsters();

        /**
         * @brief Place le joueur et les monstres à leur position de départ
         */
        void placePlayers();

    private:
        void genererGraphe();

        /**
         * @brief Place un élément au hasard sur le graphe
         * @param element Élément à placer
         * @param positionsReservees Liste des positions réservées
         * @param limit Nombre de tentatives de placement maximales
         * @throws std::runtime_exception si l'élément n'a pas pu être placé
         */
        void placerElementHasard(const Element& element, unsigned int limit = 10);

        unsigned int _width;
        unsigned int _height;

        std::map<Position<>, Sommet<Case>*, cmpPosition<>> _cases;

        Pacman _player;
        Liste<Monster>* _monsters;
};

Sommet<Case>* Board::sommet(const Position<>& position) const {
    return _cases.at(position);
}

Pacman& Board::player() {
    return _player;
}

const Pacman& Board::player() const {
    return _player;
}

Liste<Monster>* Board::monsters() {
    return _monsters;
}
