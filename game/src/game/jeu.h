#pragma once

#include <board/case.h>
#include <board/chemin.h>
#include <sprite.h>
#include <board/board.h>
#include "joueur.h"

class Jeu {
    private:
        Board* _plateau;
        Joueur* _joueur;
        Liste<Joueur>* _monstres;

    public:
        Jeu(Liste<Position>* positionMonstres);
        virtual ~Jeu();

        /**
         * @brief Donne le plateau du jeu
         * @return Plateau du jeu
         */
        Board* plateau();

        /**
         * @brief Donne le joueur
         * @return Joueur
         */
        Joueur* joueur();

        /**
         * @brief Donne la liste des monstres
         * @return Liste de monstres
         */
        Liste<Joueur>* monstres() const;
};