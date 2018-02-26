#pragma once

#include "element.h"

class Point : public Element {
    private:
        int _points;

    public:
        Point(Sprite sprite, Sound sound, int points);

        /**
         * @return Nombre de points donnés au joueur
         */
        inline int points() const;

        bool traversePar(Pacman& joueur) const override;

        Element* clone() const override;

        virtual std::string toString() const override;
};

int Point::points() const {
        return _points;
}