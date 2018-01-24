#include "pacman.h"
#include "noremaininglife.h"

Pacman::Pacman(const Position<double>& p, unsigned short nbLifes) :
        Player(p),
        _nbLifes(nbLifes) {
    _points = 0;
}

void Pacman::takeLife() {
    if(_nbLifes == 0) {
        throw NoRemainingLife("Le joueur n'a plus de vies");
    }
    _nbLifes--;
}
