#include "teleporter.h"

Teleporter::Teleporter(Sprite sprite, Sound sound, Sommet<Case>* target) :
        Element(sprite, sound),
        _target(target) {

}

bool Teleporter::traversePar(Pacman& joueur) const {
    joueur.setPosition(_target);
    return true;
}

Element* Teleporter::clone() const {
    return new Teleporter(sprite(), sound(), _target);
}
