#include <game/pacman.h>
#include "point.h"

Point::Point(Sprite sprite, Sound sound, int points) :
        Element(sprite, sound),
        _points(points) {

}

bool Point::traversePar(Pacman& joueur) const {
    joueur.addPoints(_points);
    return false;
}

Element* Point::clone() const {
    return new Point(sprite(), sound(), _points);
}
