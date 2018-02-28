#pragma once

#include "point.h"
#include <game/jeu.h>

class SuperPoint : public Point {
    public:
        SuperPoint(int points, Jeu* board);

        virtual bool traversePar(Pacman& joueur) const override;

        virtual Element* clone() const override;

        virtual void accept(ElementVisitor& visitor) override;

    private:
        Jeu* _jeu;
};