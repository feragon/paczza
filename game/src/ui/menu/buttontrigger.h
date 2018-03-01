#pragma once

#include <ui/command/command.h>

class MenuButton;
class ButtonTrigger : public Command {
    public:
        /**
         * @brief Commande qui éxecute l'action d'un bouton
         * @param menuButton Bouton
         */
        ButtonTrigger(MenuButton* menuButton);

        virtual void execute() override;

    private:
        MenuButton* _menuButton;
};