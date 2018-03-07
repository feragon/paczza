#pragma once

#include <game/gamedata.h>
#include <board/board.h>

class GameDataImpl : public GameData {
    public:
        virtual void placePlayers(Jeu* game) const override;

        virtual void placeElements(Jeu* game) const override;

        virtual GameData* clone() const override;

        /**
         * @brief Génère les sommets et arêtes du plateau
         * @param board Plateau
         */
        void genererPlateau(Board<Element>* board) const;
};