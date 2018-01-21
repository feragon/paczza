#pragma once

#include <graph/position.h>
#include <graph/liste.h>

class Joueur {
    private:
        Position _position;
        int _points;
        Liste<Position> *_deplacements;
    public:
        /**
         * @brief Crée un nouveau joueur
         */
        Joueur(Position p);

        Position position();
        void setPosition(Position p);
        Position* prochainDeplacement();
        void ajouterDeplacement(double x, double y);
        void resetDeplacement();
        int points();
        void addPoints(int pts);
};