#pragma once

#include <ui/command/command.h>
#include <game/jeu.h>

class ChangeDirectionCommand : public Command {
    public:
        /**
         * @brief Crée une commande qui change la direction du joueur
         * @param game Jeu
         * @param newDirection Nouvelle direction du joueur
         */
        ChangeDirectionCommand(Jeu* game, Direction newDirection);

        virtual void execute() override;

    private:
        Jeu* _game;
        Direction _newDirection;
};