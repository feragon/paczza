#pragma once

#include "menu.h"

class MainMenu : public Menu {
    public:
        MainMenu(sf::RenderWindow* window);

        virtual void render() override;
};