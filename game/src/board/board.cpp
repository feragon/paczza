#include <map>
#include "board.h"
#include "point.h"
#include "teleporter.h"

template <typename T = int>
class PositionsEgales {
    private:
        Position<T> _position;

    public:
        PositionsEgales(const Position<T>& position) : _position(position) {

        }

        bool operator () (const Position<T>* other) const {
            return _position == *other;
        }
};

Board::Board() :
    _player(nullptr, UP, 3) { //TODO: devrait être dans jeu
    genererGraphe();
    placePlayers();
}

void Board::genererGraphe() {
    _width = 13;
    _height = 8;

    //Création des sommets
    for(int k = (_width * _height) - 1; k >= 0; k--) {
        Position<> p((k % _width) + 1, (k / _width) + 1);
        _cases[p] = creeSommet(Case(p, nullptr));
    }

    //Maison des Monstres
    creeArete(Chemin(-1), _cases[Position<>(7,4)], _cases[Position<>(8,4)]);
    creeArete(Chemin(-1), _cases[Position<>(7,5)], _cases[Position<>(7,6)]);
    creeArete(Chemin(-1), _cases[Position<>(6,5)], _cases[Position<>(5,5)]);
    creeArete(Chemin(-1), _cases[Position<>(6,4)], _cases[Position<>(6,3)]);

    //Diags
    creeArete(Chemin(0), _cases[Position<>(1,1)], _cases[Position<>(2,2)]);
    creeArete(Chemin(0), _cases[Position<>(1,8)], _cases[Position<>(2,7)]);
    creeArete(Chemin(0), _cases[Position<>(7,2)], _cases[Position<>(8,3)]);
    creeArete(Chemin(0), _cases[Position<>(7,7)], _cases[Position<>(8,6)]);
    creeArete(Chemin(0), _cases[Position<>(11,1)], _cases[Position<>(12,2)]);
    creeArete(Chemin(0), _cases[Position<>(11,8)], _cases[Position<>(12,7)]);


    for(int j = 1; j < 8; j++)
        creeArete(Chemin(0), _cases[Position<>(1,j)], _cases[Position<>(1,j+1)]);

    creeArete(Chemin(0), _cases[Position<>(2,1)], _cases[Position<>(2,2)]);
    creeArete(Chemin(0), _cases[Position<>(2,8)], _cases[Position<>(2,7)]);
    creeArete(Chemin(0), _cases[Position<>(1,4)], _cases[Position<>(2,4)]);
    creeArete(Chemin(0), _cases[Position<>(1,5)], _cases[Position<>(2,5)]);
    creeArete(Chemin(0), _cases[Position<>(2,4)], _cases[Position<>(2,3)]);
    creeArete(Chemin(0), _cases[Position<>(2,5)], _cases[Position<>(2,6)]);
    creeArete(Chemin(0), _cases[Position<>(2,1)], _cases[Position<>(3,1)]);
    creeArete(Chemin(0), _cases[Position<>(2,8)], _cases[Position<>(3,8)]);
    creeArete(Chemin(0), _cases[Position<>(2,3)], _cases[Position<>(3,3)]);
    creeArete(Chemin(0), _cases[Position<>(2,6)], _cases[Position<>(3,6)]);

    for(int j = 2; j < 7; j++)
        creeArete(Chemin(0), _cases[Position<>(3,j)], _cases[Position<>(3,j+1)]);

    for(int i = 2; i < 13; i++) {
        creeArete(Chemin(0), _cases[Position<>(i, 2)], _cases[Position<>(i + 1, 2)]);
        creeArete(Chemin(0), _cases[Position<>(i, 7)], _cases[Position<>(i + 1, 7)]);
    }

    creeArete(Chemin(0), _cases[Position<>(3,4)], _cases[Position<>(4,4)]);
    creeArete(Chemin(0), _cases[Position<>(3,5)], _cases[Position<>(4,5)]);

    for(int j = 1; j < 8; j++)
        if(j!=4) creeArete(Chemin(0), _cases[Position<>(4,j)], _cases[Position<>(4,j+1)]);


    creeArete(Chemin(0), _cases[Position<>(6,1)], _cases[Position<>(6,2)]);
    creeArete(Chemin(0), _cases[Position<>(6,7)], _cases[Position<>(6,8)]);
    creeArete(Chemin(0), _cases[Position<>(8,1)], _cases[Position<>(8,2)]);
    creeArete(Chemin(0), _cases[Position<>(8,7)], _cases[Position<>(8,8)]);
    creeArete(Chemin(0), _cases[Position<>(9,1)], _cases[Position<>(9,2)]);
    creeArete(Chemin(0), _cases[Position<>(9,7)], _cases[Position<>(9,8)]);

    for(int j = 3; j < 6; j++) {
        creeArete(Chemin(0), _cases[Position<>(5, j)], _cases[Position<>(5, j+1)]);
        creeArete(Chemin(0), _cases[Position<>(8, j)], _cases[Position<>(8, j+1)]);
    }

    for(int i = 4; i < 8; i++) {
        creeArete(Chemin(0), _cases[Position<>(i, 3)], _cases[Position<>(i+1, 3)]);
        creeArete(Chemin(0), _cases[Position<>(i, 6)], _cases[Position<>(i+1, 6)]);
    }

    creeArete(Chemin(0), _cases[Position<>(6,2)], _cases[Position<>(6,3)]);
    creeArete(Chemin(0), _cases[Position<>(6,6)], _cases[Position<>(6,7)]);
    creeArete(Chemin(0), _cases[Position<>(8,1)], _cases[Position<>(9,1)]);
    creeArete(Chemin(0), _cases[Position<>(8,8)], _cases[Position<>(9,8)]);
    creeArete(Chemin(0), _cases[Position<>(8,4)], _cases[Position<>(9,4)]);
    creeArete(Chemin(0), _cases[Position<>(8,5)], _cases[Position<>(9,5)]);
    creeArete(Chemin(0), _cases[Position<>(9,4)], _cases[Position<>(9,3)]);
    creeArete(Chemin(0), _cases[Position<>(9,5)], _cases[Position<>(9,6)]);
    creeArete(Chemin(0), _cases[Position<>(9,3)], _cases[Position<>(10,3)]);
    creeArete(Chemin(0), _cases[Position<>(9,6)], _cases[Position<>(10,6)]);

    creeArete(Chemin(0), _cases[Position<>(12,8)], _cases[Position<>(13,8)]);
    creeArete(Chemin(0), _cases[Position<>(12,1)], _cases[Position<>(13,1)]);
    creeArete(Chemin(0), _cases[Position<>(3,1)], _cases[Position<>(4,1)]);
    creeArete(Chemin(0), _cases[Position<>(3,8)], _cases[Position<>(4,8)]);

    for(int j = 1; j < 8; j++)
        creeArete(Chemin(0), _cases[Position<>(10,j)], _cases[Position<>(10,j+1)]);

    creeArete(Chemin(0), _cases[Position<>(10,4)], _cases[Position<>(11,4)]);
    creeArete(Chemin(0), _cases[Position<>(10,5)], _cases[Position<>(11,5)]);
    creeArete(Chemin(0), _cases[Position<>(11,4)], _cases[Position<>(12,4)]);
    creeArete(Chemin(0), _cases[Position<>(11,5)], _cases[Position<>(12,5)]);
    creeArete(Chemin(0), _cases[Position<>(12,2)], _cases[Position<>(12,3)]);
    creeArete(Chemin(0), _cases[Position<>(12,3)], _cases[Position<>(12,4)]);
    creeArete(Chemin(0), _cases[Position<>(12,5)], _cases[Position<>(12,6)]);
    creeArete(Chemin(0), _cases[Position<>(12,6)], _cases[Position<>(12,7)]);
    creeArete(Chemin(0), _cases[Position<>(10,1)], _cases[Position<>(11,1)]);
    creeArete(Chemin(0), _cases[Position<>(11,1)], _cases[Position<>(12,1)]);
    creeArete(Chemin(0), _cases[Position<>(10,8)], _cases[Position<>(11,8)]);
    creeArete(Chemin(0), _cases[Position<>(11,8)], _cases[Position<>(12,8)]);
    creeArete(Chemin(0), _cases[Position<>(13,1)], _cases[Position<>(13,2)]);
    creeArete(Chemin(0), _cases[Position<>(13,2)], _cases[Position<>(13,3)]);
    creeArete(Chemin(0), _cases[Position<>(13,6)], _cases[Position<>(13,7)]);
    creeArete(Chemin(0), _cases[Position<>(13,7)], _cases[Position<>(13,8)]);
    creeArete(Chemin(0), _cases[Position<>(12,3)], _cases[Position<>(13,3)]);
    creeArete(Chemin(0), _cases[Position<>(12,6)], _cases[Position<>(13,6)]);
    creeArete(Chemin(0), _cases[Position<>(11,3)], _cases[Position<>(12,3)]);
    creeArete(Chemin(0), _cases[Position<>(11,6)], _cases[Position<>(12,6)]);

    Teleporter t1(TELEPORTER, TELEPORT, _cases[Position<>(6,2)]);
    Teleporter t2(TELEPORTER, TELEPORT, _cases[Position<>(6,7)]);
    _cases[Position<>(6,8)]->contenu().setElement(&t1);
    _cases[Position<>(6,1)]->contenu().setElement(&t2);

    //Placement des points
    try {
        placerElementHasard(Point(TOMATO, BONUS, 50));
        placerElementHasard(Point(CHEESE, BONUS, 50));
        placerElementHasard(Point(HAM, BONUS, 50));
        placerElementHasard(Point(MUSHROOM, BONUS, 50));
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    for(Liste<Sommet<Case>>* l = sommets(); l; l = l->next) {
        if(l->value->degre() > 0 &&
           !l->value->contenu().element()) {

            Point element(TOMATO_SMUDGE, EAT, 10);
            l->value->contenu().setElement(&element);
        }
    }
}

void Board::placerElementHasard(const Element& element, unsigned int limit) {
    unsigned int i = 1;
    Position<> p((rand() % _width) + 1, (rand() % _height) + 1);

    while(sommet(p)->contenu().element()) {
        if(i == limit) {
            throw std::runtime_error("Impossible de placer les éléments");
        }

        p = Position<>((rand() % _width) + 1, (rand() % _height) + 1);

        i++;
    }

    sommet(p)->contenu().setElement(&element);
}

void Board::placePlayers() {
    _player.setPosition(_cases[Position<>(3,5)]);
    _player.setDirection(UP);

    Liste<Monster>::efface2(_monsters);
    _monsters = new Liste<Monster>(new Monster(_cases[Position<>(6,4)], UP), _monsters);
    _monsters = new Liste<Monster>(new Monster(_cases[Position<>(6,5)], UP), _monsters);
    _monsters = new Liste<Monster>(new Monster(_cases[Position<>(7,4)], UP), _monsters);
    _monsters = new Liste<Monster>(new Monster(_cases[Position<>(7,5)], UP), _monsters);
}
