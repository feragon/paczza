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
        Position<> getNextPlayerPosition();

        Board* _plateau;
        Pacman* _joueur;
        Liste<Monster>* _monstres;
        std::map<Player*, Position<>> _oldPositions;
        MonsterManager* _monsterManager;
        double _timeSinceMove;
        Position<double> _newPlayerPosition;
        Direction _direction;
        Direction _newDirection;
        OnPlayerPositionChanged* _onPlayerPositionChanged;
        bool _gameOver;

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
         * @brief Change la direction du joueur
         * @param newPosition Nouvelle direction
         */
        inline void setDirection(Direction newDirection);

        /**
         * @brief Donne la direction actuelle du joueur
         * @return Direction
         */
        inline Direction direction() const;

        /**
         * @brief Définit la fonction appelée quand le joueur arrive sur une nouvelle case
         * @param onPlayerPositionChanged Fonction appelée
         */
        inline void setOnPlayerPositionChanged(OnPlayerPositionChanged* onPlayerPositionChanged);

        /**
         * @brief Donne l'état du jeu
         * @return Vrai si le joueur a perdu
         */
        inline bool gameOver() const;
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

Direction Jeu::direction() const {
    return _direction;
}

void Jeu::setOnPlayerPositionChanged(OnPlayerPositionChanged* onPlayerPositionChanged) {
    _onPlayerPositionChanged = onPlayerPositionChanged;
}

bool Jeu::gameOver() const {
    return _gameOver;
}