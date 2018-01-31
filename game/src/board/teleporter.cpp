#include "teleporter.h"

Teleporter::Teleporter(Sprite sprite, Sommet<Case>* target) :
        Element(sprite),
        _target(target) {

}

bool Teleporter::traversePar(Pacman& joueur) const {
    joueur.setPosition(_target);
    return true;
}

Element* Teleporter::clone() const {
    return new Teleporter(sprite(), _target);
}
