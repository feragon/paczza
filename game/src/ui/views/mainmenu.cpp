#include <iostream>
#include <game/jeu.h>
#include "mainmenu.h"

MainMenu::MainMenu(sf::RenderWindow* window) :
    Menu(window) {

    addMenu(L"Nouvelle partie", std::bind(&MainMenu::onNewGameSelected, this));
    addMenu(L"Meilleurs scores", std::bind(&MainMenu::onHighScoreSelected, this));
    addMenu(L"Crédits", std::bind(&MainMenu::onCreditsSelected, this));
    addMenu(L"Quitter", std::bind(&MainMenu::onExitSelected, this));
}

void MainMenu::onNewGameSelected() {
    Jeu *j = new Jeu(4);
    _window->close();
}

void MainMenu::onHighScoreSelected() {

}

void MainMenu::onCreditsSelected() {

}

void MainMenu::onExitSelected() {
    _window->close();
}
