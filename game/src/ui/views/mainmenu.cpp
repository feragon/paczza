#include "mainmenu.h"

MainMenu::MainMenu(sf::RenderWindow* window) :
    Menu(window) {

    addMenu(L"Nouvelle partie");
    addMenu(L"Meilleurs scores");
    addMenu(L"Crédits");
}