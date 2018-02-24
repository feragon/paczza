#pragma once

#include "jeu.h"

class PacmanGame : public Jeu {
    public:
        PacmanGame();

        void start() override;

        /**
         * @brief Donne le niveau actuel
         * @return Niveau
         */
        inline unsigned short level() const;

    private:
        /**
         * @brief Passe au niveau suivant
         */
        void changeLevel();

        unsigned short _level;
        std::vector<SharedPtr<MonsterManager>> _levels;
};

unsigned short PacmanGame::level() const {
    return _level;
}