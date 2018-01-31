#pragma once

#include "element.h"

class Teleporter : public Element {
    public:
        Teleporter(Sprite sprite, Sommet<Case>* target);

        virtual bool traversePar(Pacman& joueur) const override;

        virtual Element* clone() const override;

    private:
        Sommet<Case>* _target;
};