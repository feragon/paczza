#pragma once

#include "element.h"

class Point : public Element {
    private:
        int _points;

    public:
        Point(Sprite sprite, int points);

        bool traversePar(Pacman& joueur) const override;

        Element* clone() const override;
};