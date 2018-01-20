#include <map>
#include "board.h"
#include "point.h"

class PositionsEgales {
    private:
        Position _position;

    public:
        PositionsEgales(const Position& position) : _position(position) {

        }

        bool operator () (const Position* other) const {
            return _position == *other;
        }
};

Board::Board(unsigned int width, unsigned int height, Liste<Position>* positionsReservees) {
    _width = width;
    _height = height;

    genererGraphe(positionsReservees);
}

void Board::genererGraphe(Liste<Position>* positionsReservees) {
    int nb, alea_x1, alea_y1, alea_x2, alea_y2;
    srand(time(NULL));

    //Création des sommets
    for(int k = (_width * _height) - 1; k >= 0; k--) {
        Position p((k % _width) + 1, (k / _width) + 1);
        _cases[p] = creeSommet(Case(p, nullptr));
    }

    //Création des arêtes diagonales
    for(int i = 0; i < _width; i++) {
        //Coordonnees Sommet1 aleatoire
        alea_x1 = rand() % _width + 1;
        alea_y1 = rand() % _height + 1;

        //Coordonnees Sommet2 voisin aleatoire
        alea_x2 = alea_x1 % 3 ? alea_x1 - 1 : alea_x1 + 1;
        alea_y2 = alea_y1 % 3 ? alea_y1 - 1 : alea_y1 + 1;

        //si Sommet1 est sur un bord, on force la position de Sommet2
        if(alea_x1 == 1) alea_x2 = alea_x1+1;
        if(alea_x1 == _width) alea_x2 = alea_x1-1;
        if(alea_y1 == 1) alea_y2 = alea_y1+1;
        if(alea_y1 == _height) alea_y2 = alea_y1-1;

        creeArete(Chemin(0), _cases[Position(alea_x1, alea_y1)], _cases[Position(alea_x2, alea_y2)]);
    }

    //Création des arêtes droites
    for(int i = 1; i <= _height; i++) {
        for(int j = 1; j <= _width; j++) {

            nb = rand() % 100;
            if(nb < 80 && j < _width) {
                Position p1(j, i);
                Position p2(j + 1, i);
                creeArete(Chemin(0), _cases[p1], _cases[p2]);
            }

            nb = rand() % 100;
            if(nb < 55 && i < _height) {
                Position p1(j, i);
                Position p2(j, i + 1);
                creeArete(Chemin(0), _cases[p1], _cases[p2]);
            }
        }
    }

    //Placement des points
    try {
        placerElementHasard(Point(TOMATO, 50), positionsReservees);
        placerElementHasard(Point(CHEESE, 50), positionsReservees);
        placerElementHasard(Point(HAM, 50), positionsReservees);
        placerElementHasard(Point(MUSHROOM, 50), positionsReservees);
    }
    catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

    for(Liste<Sommet<Case>>* l = sommets(); l; l = l->next) {
        if(l->value->degre() > 0 &&
           !l->value->contenu().element() &&
           !Liste<Position>::appartient(positionsReservees, PositionsEgales(l->value->contenu().position()))) {

            Point element(TOMATO_SMUDGE, 10);
            l->value->contenu().setElement(&element);
        }
    }
}

void Board::placerElementHasard(const Element& element, Liste<Position>* positionsReservees, unsigned int limit) {
    unsigned int i = 1;
    Position p((rand() % _width) + 1, (rand() % _height) + 1);

    while(sommet(p)->contenu().element() || Liste<Position>::appartient(positionsReservees, PositionsEgales(p))) {
        if(i == limit) {
            throw std::runtime_error("Impossible de placer les éléments");
        }

        p = Position((rand() % _width) + 1, (rand() % _height) + 1);

        i++;
    }

    sommet(p)->contenu().setElement(&element);
}
