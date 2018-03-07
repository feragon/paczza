#pragma once

#include <config.h>
#include "player.h"
#include "direction.h"
#include "pacman.h"

class Monster : public Player {
    public:
        /**
         * @brief Crée un monstre
         * @param p Position du monstre
         * @param direction Direction
         * @param home Position d'origine
         */
        Monster(const Sommet<Case<Element>>* p, Direction direction, Sommet<Case<Element>>* home);

        /**
         * @return Vrai si le monstre est vulnérable
         */
        inline bool weak() const;

        /**
         * @brief Définit la vulnérabilité
         * @param isWeak Nouvelle vulnérabilité
         */
        void setWeak(bool isWeak);

        /**
         * @return Vrai si le monstre doit retourner à sa position originale
         */
        inline bool returnHome() const;

        /**
         * @brief Définit la destination du monstre
         * @param returnHome Vrai si le monstre doit retourner à sa position originale
         */
        inline void setReturnHome(bool returnHome);

        virtual std::string toString() const override;

        /**
         * @brief Donne la position originale du monstre
         * @return Position originale du monstre
         */
        inline Sommet<Case<Element>>* home() const;

        /**
         * @brief Fonction appelée lors de la collision avec le joueur
         * @param pacman Joueur
         * @throw PacmanDied si la collision fait perdre le joueur
         */
        void collision(Pacman& pacman);

        /**
         * @brief Donne le temps de vulnérabilité restant
         * @return Temps de vulnérabilité restant
         */
        inline double weakTime() const;

        /**
         * @brief Met à jour le monstre
         * @param timeElapsed Temps écoulé depuis la dernière mise à jour
         * @return Vrai si l'état du monstre a changé
         */
        bool update(double timeElapsed);

    private:
        bool _returnHome;
        double _weakTime;
        Sommet<Case<Element>>* _home;
};

bool Monster::weak() const {
    return _weakTime > 0 || _returnHome;
}

bool Monster::returnHome() const {
    return _returnHome;
}

void Monster::setReturnHome(bool returnHome) {
    _returnHome = returnHome;
}

Sommet<Case<Element>>* Monster::home() const {
    return _home;
}

double Monster::weakTime() const {
    return _weakTime;
}
