#include "teleporter.h"
#include "board/case.h"
#include "pacman.h"

Teleporter::Teleporter(Sommet<Case<Element>>* target) :
        Element(),
        _target(target) {

}

bool Teleporter::traversePar(Pacman& joueur) const {
    joueur.setPosition(_target);
    return true;
}

Element* Teleporter::clone() const {
    return new Teleporter(_target);
}

std::string Teleporter::toString() const {
    std::ostringstream oss;
    oss << "Teleporter(" << Element::toString() << "; _target" << _target << ")";
    return oss.str();
}

void Teleporter::accept(ElementVisitor& visitor) {
    visitor.visite(*this);
}
