#include <game/jeu.h>
#include "superpoint.h"

SuperPoint::SuperPoint(Sprite sprite, Sound sound, int points, Jeu* jeu) :
        Point(sprite, sound, points) {
    _jeu = jeu;
}

bool SuperPoint::traversePar(Pacman& joueur) const {
    _jeu->setMonstersWeak();
    return Point::traversePar(joueur);
}

Element* SuperPoint::clone() const {
    return new SuperPoint(sprite(), sound(), points(), _jeu);
}
