#include <map>
#include "board.h"

Board::Board(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;

    genererGraphe();
}

void Board::genererGraphe() {
    int nb, alea_x1, alea_y1, alea_x2, alea_y2;
    srand(time(NULL));

    //Création des sommets
    for(int k = (_width * _height) - 1; k >= 0; k--) {
        Position p((k % _width) + 1, (k / _width) + 1);
        _cases[p] = creeSommet(p);
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
}