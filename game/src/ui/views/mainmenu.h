#pragma once

#include "ui/menu/menu.h"

class MainMenu : public Menu {
    public:
        MainMenu(sf::RenderWindow* window, FenetreJeu* f);

    private:
        void onNewGameSelected();
        void onHighScoreSelected();
        void onCreditsSelected();
        void onExitSelected();
};