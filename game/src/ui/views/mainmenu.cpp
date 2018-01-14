#include <iostream>
#include "mainmenu.h"

MainMenu::MainMenu(sf::RenderWindow* window) :
    Menu(window) {

    addMenu(L"Nouvelle partie", std::bind(&MainMenu::onNewGameSelected, this));
    addMenu(L"Meilleurs scores", std::bind(&MainMenu::onHighScoreSelected, this));
    addMenu(L"Crédits", std::bind(&MainMenu::onCreditsSelected, this));
}

void MainMenu::onNewGameSelected() {
    _window->close();
}

void MainMenu::onHighScoreSelected() {

}

void MainMenu::onCreditsSelected() {

}
