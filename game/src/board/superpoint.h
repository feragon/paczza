#pragma once

#include "point.h"
#include <game/jeu.h>

class SuperPoint : public Point {
    public:
        SuperPoint(Sprite sprite, Sound sound, int points, Jeu* board);

        virtual bool traversePar(Pacman& joueur) const override;

        virtual Element* clone() const override;

    private:
        Jeu* _jeu;
};