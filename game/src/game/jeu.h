#pragma once

#include <board/case.h>
#include <board/chemin.h>
#include <sprite.h>
#include <board/board.h>
#include "player.h"
#include "monstermanager.h"

class Jeu {
    private:
        Board* _plateau;
        Pacman* _joueur;
        Liste<Monster>* _monstres;
        MonsterManager* _monsterManager;
        double _timeSinceMove;

    public:
        Jeu();
        virtual ~Jeu();

        /**
         * @brief Donne le plateau du jeu
         * @return Plateau du jeu
         */
        inline Board* plateau();

        /**
         * @brief Donne le joueur
         * @return Joueur
         */
        inline Pacman* joueur();

        /**
         * @brief Donne la liste des monstres
         * @return Liste de monstres
         */
        inline Liste<Monster>* monstres() const;

        /**
         * @brief Met à jour la partie
         * @param timeElapsed Temps écoulé depuis la dernière mise à jour
         */
        void updateGame(double timeElapsed);
};

Board* Jeu::plateau() {
    return _plateau;
};

Pacman* Jeu::joueur() {
    return _joueur;
}

Liste<Monster>* Jeu::monstres() const {
    return _monstres;
}
