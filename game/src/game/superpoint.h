#pragma once

#include "point.h"
#include <game/jeu.h>

class SuperPoint : public Point {
    public:
        /**
         * @brief Crée un élément rapportant des points au joueur et rendant les monstres vulnérables
         * @param points Nombre de points
         * @param game Jeu utilisé
         */
        SuperPoint(int points, Jeu* game);

        virtual bool traversePar(Pacman& joueur) const override;

        virtual Element* clone() const override;

        virtual void accept(ElementVisitor& visitor) override;

    private:
        Jeu* _jeu;
};