#include <game/pacman.h>
#include "point.h"

Point::Point(int points) :
        Element(),
        _points(points) {

}

bool Point::traversePar(Pacman& joueur) const {
    joueur.addPoints(_points);
    return false;
}

Element* Point::clone() const {
    return new Point(_points);
}

std::string Point::toString() const {
    std::ostringstream oss;
    oss << "Point(" << Element::toString() << "; _points" << _points << ")";
    return oss.str();
}

void Point::accept(ElementVisitor& visitor) {
    visitor.visite(*this);
}