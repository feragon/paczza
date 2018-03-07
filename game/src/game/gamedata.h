#pragma once

class Jeu;

class GameData {
    public:
        /**
         * @brief Place les joueurs dans le jeu
         * @param game Jeu
         */
        virtual void placePlayers(Jeu* game) const = 0;

        /**
         * @brief Place les éléments sur le plateau
         * @param game Jeu
         */
        virtual void placeElements(Jeu* game) const = 0;

        /**
         * @brief Clone cet objet
         * @return Clone
         */
        virtual GameData* clone() const = 0;
};