#pragma once

#include <board/case.h>
#include <board/chemin.h>
#include <sprite.h>
#include <board/board.h>
#include "player.h"
#include "monstermanager.h"
#include "direction.h"
#include "boardlistener.h"

class Jeu : public Listened<BoardListener> {
    private:
        Sommet<Case>* getNextPlayerPosition();
        void updateOldPositions();

        Board* _plateau;
        std::map<Player*, const Sommet<Case>*> _oldPositions;
        MonsterManager* _monsterManager;
        double _timeSinceMove;
        Sommet<Case>* _newPlayerPosition;
        Direction _newDirection;
        bool _stopped;

        unsigned int _remainingPoints;

    public:
        Jeu();
        virtual ~Jeu();

        /**
         * @brief Remet a zéro la partie
         */
        void updatePoints();

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
         * @brief Donne le gestionnaire de monstres
         * @return MonsterManager
         */
        inline const MonsterManager* monsterManager() const;

        /**
         * @brief Donne le nombre de points restant sur le plateau
         * @return Nombre de points
         */
        inline unsigned int remainingPoints() const;

        /**
         * @brief Met à jour la partie
         * @param timeElapsed Temps écoulé depuis la dernière mise à jour
         */
        void updateGame(double timeElapsed);

        /**
         * @brief Met à jour les joueurs
         * @param timeElapsed Temps écoulé depuis la dernière mise à jour
         */
        void updatePlayers(double timeElapsed);

        /**
         * @brief Change la nouvelle direction du joueur
         * @param newPosition Nouvelle direction
         */
        inline void setDirection(Direction newDirection);

        /**
         * @brief Change le gestionnaire de monstres
         * @param monsterManager Nouveau gestionnaire
         */
        void setMonsterManager(MonsterManager* monsterManager);

        /**
         * @brief Donne l'état du jeu
         * @return Vrai si le jeu est en pause
         */
        inline bool stopped() const;

        /**
         * @brief Démarre la partie
         */
        virtual void start();
};

Board* Jeu::plateau() {
    return _plateau;
};

Pacman* Jeu::joueur() {
    return &(_plateau->player()); //TODO
}

Liste<Monster>* Jeu::monstres() const {
    return _plateau->monsters();
}

void Jeu::setDirection(Direction newDirection) {
    _newDirection = newDirection;
}

bool Jeu::stopped() const {
    return _stopped;
}

const MonsterManager* Jeu::monsterManager() const {
    return _monsterManager;
}

unsigned int Jeu::remainingPoints() const {
    return _remainingPoints;
}

