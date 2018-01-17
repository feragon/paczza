#include <map>
#include "board.h"

Board::Board(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;

    genererGraphe();
}

void Board::genererGraphe() {
    srand(time(NULL));

    for(int k = (_width * _height) - 1; k >= 0; k--) {
        Position p((k % _width) + 1, (k / _width) + 1);
        _cases[p] = creeSommet(p);
    }

    for(int i = 1; i <= _height; i++) {
        for(int j = 1; j <= _width; j++) {

            int nb = rand() % 100;
            if (nb < 80) {

                /* Ca fait un quadrillage :) */
                if(j < _width) {
                    Position p1(j, i);
                    Position p2(j + 1, i);
                    creeArete(Chemin(0), _cases[p1], _cases[p2]);
                }
                if(i < _height) {
                    Position p1(j, i);
                    Position p2(j, i + 1);
                    creeArete(Chemin(0), _cases[p1], _cases[p2]);
                }
            }
        }
    }

    creeArete(Chemin(0), _cases[Position(3, 2)], _cases[Position(2, 1)]);
    creeArete(Chemin(0), _cases[Position(5, 4)], _cases[Position(4, 5)]);
}