#include <game/jeu.h>
#include "superpoint.h"

SuperPoint::SuperPoint(int points, Jeu* game) :
        Point(points) {
    _jeu = game;
}

bool SuperPoint::traversePar(Pacman& joueur) const {
    _jeu->setMonstersWeak();
    return Point::traversePar(joueur);
}

Element* SuperPoint::clone() const {
    return new SuperPoint(points(), _jeu);
}

void SuperPoint::accept(ElementVisitor& visitor) {
    visitor.visite(*this);
}
