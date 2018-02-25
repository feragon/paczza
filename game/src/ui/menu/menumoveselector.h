#pragma once

#include <ui/command/command.h>

class Menu;

class MenuMoveSelector : public Command {
    public:
        MenuMoveSelector(Menu* menu, long offset);

        virtual void execute() override;

    private:
        Menu* _menu;
        long _offset;
};