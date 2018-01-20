#pragma once

#include "element.h"

class Point : public Element {
    private:
        int _points;

    public:
        Point(Sprite sprite, int points);

        bool traversePar(Joueur& joueur) const override;

        Element* clone() const override;
};