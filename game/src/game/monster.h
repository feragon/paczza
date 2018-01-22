#pragma once

#include "player.h"

class Monster : public Player {
    public:
        Monster(const Position<double>& p);

        /**
         * @return Vrai si le monstre est vulnérable
         */
        inline bool weak() const;

        /**
         * @brief Définit la vulnérabilité
         * @param isWeak Nouvelle vulnérabilité
         */
        inline void setWeak(bool isWeak);

    private:
        bool _isWeak;
};

bool Monster::weak() const {
    return _isWeak;
}

void Monster::setWeak(bool isWeak) {
    _isWeak = isWeak;
}
