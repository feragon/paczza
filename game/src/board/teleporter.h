#pragma once

#include "element.h"

class Teleporter : public Element {
    public:
        Teleporter(Sommet<Case>* target);

        virtual bool traversePar(Pacman& joueur) const override;

        virtual Element* clone() const override;

        virtual void accept(ElementVisitor& visitor) override;

        virtual std::string toString() const override;

    private:
        Sommet<Case>* _target;
};