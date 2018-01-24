#pragma once

#include "player.h"
#include "direction.h"

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

        inline Direction direction();
        inline void setDirection(Direction d);

    private:
        bool _isWeak;
        Direction _direction;
};

bool Monster::weak() const {
    return _isWeak;
}

void Monster::setWeak(bool isWeak) {
    _isWeak = isWeak;
}

Direction Monster::direction() {
    return _direction;
}

void Monster::setDirection(Direction d) {
    _direction = d;
}