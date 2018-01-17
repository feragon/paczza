#pragma once

#include <graph/position.h>
#include <sprite.h>

class ElementGraphique {
private:
    Position _position;
    Sprite _sprite;
    int _points;
public:
    ElementGraphique(Position pos, Sprite sp, int pts);

    inline Position position();
    inline Sprite sprite();
    inline int points();
};

Position ElementGraphique::position() {
    return _position;
}

Sprite ElementGraphique::sprite() {
    return _sprite;
}

int ElementGraphique::points() {
    return _points;
}