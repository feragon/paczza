#pragma once

#include <ui/command/command.h>
#include "pacmangameview.h"

class StartGameCommand : public Command {
    public:
        /**
         * @brief Crée une commande qui démarre la partie
         * @param view Vue du jeu
         */
        StartGameCommand(PacmanGameView* view);

        virtual void execute() override;

    private:
        PacmanGameView* _view;
};