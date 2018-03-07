#include "pacman.h"
#include "noremaininglife.h"

Pacman::Pacman(const Sommet<Case<Element>>* p, Direction direction, unsigned short nbLifes) :
        Player(p, direction),
        _nbLifes(nbLifes) {
    _points = 0;
}

void Pacman::takeLife() {
    if(_nbLifes == 0) {
        throw NoRemainingLife("Le joueur n'a plus de vies");
    }
    _nbLifes--;
}

std::string Pacman::toString() const {
    std::ostringstream oss;
    oss << "Pacman(" << Player::toString() << "; "
        << "_points=" << _points << "; "
        << "_nbLifes" << _nbLifes << ")";
    return oss.str();
}
