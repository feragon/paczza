#pragma once

#include <ui/command/command.h>

class Menu;

class MenuMoveSelector : public Command {
    public:
        /**
         * @brief Commande qui déplace le selecteur d'un menu
         * @param menu Menu
         * @param offset Décalage
         */
        MenuMoveSelector(Menu* menu, long offset);

        virtual void execute() override;

    private:
        Menu* _menu;
        long _offset;
};