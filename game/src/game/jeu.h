#pragma once

#include <board/case.h>
#include <board/chemin.h>
#include <sprite.h>
#include <board/board.h>
#include <util/shared_ptr.h>
#include "player.h"
#include "monstermanager.h"
#include "direction.h"
#include "boardlistener.h"
#include "element.h"

class Jeu : public Listened<BoardListener> {
    private:
        Sommet<Case<Element>>* getNextPlayerPosition();
        void updateOldPositions();
        /**
         * @brief Ajoute un monstre au jeu
         * @param position Position du monstre
         */
        void addMonster(Sommet<Case<Element>>* position);

        Board<Element>* _plateau;
        std::map<Player*, const Sommet<Case<Element>>*> _oldPositions;
        SharedPtr<MonsterManager> _monsterManager;
        double _timeSinceMove;
        Sommet<Case<Element>>* _newPlayerPosition;
        Direction _newDirection;
        bool _stopped;

        unsigned int _remainingPoints;

        Pacman _player;
        Liste<Monster>* _monsters;
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
        inline Board<Element>* plateau();

        /**
         * @brief Donne le gestionnaire de monstres
         * @return MonsterManager
         */
        inline SharedPtr<const MonsterManager> monsterManager() const;

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
        inline void setMonsterManager(SharedPtr<MonsterManager> monsterManager);

        /**
         * @brief Donne l'état du jeu
         * @return Vrai si le jeu est en pause
         */
        inline bool stopped() const;

        /**
         * @brief Démarre la partie
         */
        virtual void start();

        /**
         * @brief Rend tous les monstres vulnérables
         */
        void setMonstersWeak();

        /**
         * @brief Place les éléments sur le plateau
         */
        void placeElements();

        /**
         * @brief Place le joueur et les monstres à leur position de départ
         */
        void placePlayers();

        /**
         * @brief Donne le joueur
         * @return Pacman
         */
        inline Pacman& player();

        /**
         * @brief Donne le joueur
         * @return Pacman constant
         */
        inline const Pacman& player() const;

        /**
         * @brief Donne la liste des monstres sur le plateau
         * @return Liste de monstres
         */
        inline Liste<Monster>* monsters();
};

Board<Element>* Jeu::plateau() {
    return _plateau;
};

void Jeu::setDirection(Direction newDirection) {
    _newDirection = newDirection;
}

bool Jeu::stopped() const {
    return _stopped;
}

SharedPtr<const MonsterManager> Jeu::monsterManager() const {
    return _monsterManager;
}

unsigned int Jeu::remainingPoints() const {
    return _remainingPoints;
}

void Jeu::setMonsterManager(SharedPtr<MonsterManager> monsterManager) {
    _monsterManager = monsterManager;
}

Pacman& Jeu::player() {
    return _player;
}

const Pacman& Jeu::player() const {
    return _player;
}

Liste<Monster>* Jeu::monsters() {
    return _monsters;
}