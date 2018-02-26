#pragma once

#include "player.h"
#include "direction.h"

class Monster : public Player {
    public:
        Monster(const Sommet<Case>* p, Direction direction, Sommet<Case>* home);

        /**
         * @return Vrai si le monstre est vulnérable
         */
        inline bool weak() const;

        /**
         * @brief Définit la vulnérabilité
         * @param isWeak Nouvelle vulnérabilité
         */
        inline void setWeak(bool isWeak);

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
        inline Sommet<Case>* home() const;

    private:
        bool _isWeak;
        bool _returnHome;
        Sommet<Case>* _home;
};

bool Monster::weak() const {
    return _isWeak;
}

void Monster::setWeak(bool isWeak) {
    _isWeak = isWeak;
}

bool Monster::returnHome() const {
    return _returnHome;
}

void Monster::setReturnHome(bool returnHome) {
    _returnHome = returnHome;
}

Sommet<Case>* Monster::home() const {
    return _home;
}