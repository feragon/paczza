#pragma once

#include <board/case.h>
#include <board/chemin.h>
#include <sprite.h>
#include <board/board.h>
#include "player.h"
#include "monstermanager.h"
#include "direction.h"
#include "onplayerpositionchanged.h"

class Jeu {
    private:
        Sommet<Case>* getNextPlayerPosition();

        Board* _plateau;
        Pacman* _joueur;
        Liste<Monster>* _monstres;
        std::map<Player*, const Sommet<Case>*> _oldPositions;
        MonsterManager* _monsterManager;
        double _timeSinceMove;
        Sommet<Case>* _newPlayerPosition;
        Direction _newDirection;
        OnPlayerPositionChanged* _onPlayerPositionChanged;
        bool _stopped;

        Position<> _originalPlayerPosition;
        std::vector<Position<>> _originalMonstersPositions;

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
         * @brief Définit la fonction appelée quand le joueur arrive sur une nouvelle case
         * @param onPlayerPositionChanged Fonction appelée
         */
        inline void setOnPlayerPositionChanged(OnPlayerPositionChanged* onPlayerPositionChanged);

        /**
         * @brief Donne l'état du jeu
         * @return Vrai si le jeu est en pause
         */
        inline bool stopped() const;

        /**
         * @brief Démarre la partie
         */
        void start();
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

void Jeu::setDirection(Direction newDirection) {
    _newDirection = newDirection;
}

void Jeu::setOnPlayerPositionChanged(OnPlayerPositionChanged* onPlayerPositionChanged) {
    _onPlayerPositionChanged = onPlayerPositionChanged;
}

bool Jeu::stopped() const {
    return _stopped;
}