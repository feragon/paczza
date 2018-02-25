#pragma once

#include <ui/command/command.h>

class MenuButton;
class ButtonTrigger : public Command {
    public:
        ButtonTrigger(MenuButton* menuButton);

        virtual void execute() override;

    private:
        MenuButton* _menuButton;
};