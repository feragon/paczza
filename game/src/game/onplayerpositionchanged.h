#pragma once

#include <board/position.h>

class OnPlayerPositionChanged {
    public:
        /**
         * @brief Fonction appelée quand le joueur s'est déplacé de case
         * @param oldPosition Ancienne position
         * @param newPosition Nouvelle position
         */
        virtual void onPlayerPositionChanged(const Position<>& oldPosition, const Position<>& newPosition) = 0;
};